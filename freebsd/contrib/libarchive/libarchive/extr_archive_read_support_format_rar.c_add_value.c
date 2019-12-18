#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct huffman_code {int maxlength; int minlength; TYPE_1__* tree; int /*<<< orphan*/  numentries; int /*<<< orphan*/ * table; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct TYPE_2__ {int* branches; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int new_node (struct huffman_code*) ; 

__attribute__((used)) static int
add_value(struct archive_read *a, struct huffman_code *code, int value,
          int codebits, int length)
{
  int repeatpos, lastnode, bitpos, bit, repeatnode, nextnode;

  free(code->table);
  code->table = NULL;

  if(length > code->maxlength)
    code->maxlength = length;
  if(length < code->minlength)
    code->minlength = length;

  repeatpos = -1;
  if (repeatpos == 0 || (repeatpos >= 0
    && (((codebits >> (repeatpos - 1)) & 3) == 0
    || ((codebits >> (repeatpos - 1)) & 3) == 3)))
  {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Invalid repeat position");
    return (ARCHIVE_FATAL);
  }

  lastnode = 0;
  for (bitpos = length - 1; bitpos >= 0; bitpos--)
  {
    bit = (codebits >> bitpos) & 1;

    /* Leaf node check */
    if (code->tree[lastnode].branches[0] ==
      code->tree[lastnode].branches[1])
    {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Prefix found");
      return (ARCHIVE_FATAL);
    }

    if (bitpos == repeatpos)
    {
      /* Open branch check */
      if (!(code->tree[lastnode].branches[bit] < 0))
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Invalid repeating code");
        return (ARCHIVE_FATAL);
      }

      if ((repeatnode = new_node(code)) < 0) {
        archive_set_error(&a->archive, ENOMEM,
                          "Unable to allocate memory for node data.");
        return (ARCHIVE_FATAL);
      }
      if ((nextnode = new_node(code)) < 0) {
        archive_set_error(&a->archive, ENOMEM,
                          "Unable to allocate memory for node data.");
        return (ARCHIVE_FATAL);
      }

      /* Set branches */
      code->tree[lastnode].branches[bit] = repeatnode;
      code->tree[repeatnode].branches[bit] = repeatnode;
      code->tree[repeatnode].branches[bit^1] = nextnode;
      lastnode = nextnode;

      bitpos++; /* terminating bit already handled, skip it */
    }
    else
    {
      /* Open branch check */
      if (code->tree[lastnode].branches[bit] < 0)
      {
        if (new_node(code) < 0) {
          archive_set_error(&a->archive, ENOMEM,
                            "Unable to allocate memory for node data.");
          return (ARCHIVE_FATAL);
        }
        code->tree[lastnode].branches[bit] = code->numentries++;
      }

      /* set to branch */
      lastnode = code->tree[lastnode].branches[bit];
    }
  }

  if (!(code->tree[lastnode].branches[0] == -1
    && code->tree[lastnode].branches[1] == -2))
  {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Prefix found");
    return (ARCHIVE_FATAL);
  }

  /* Set leaf value */
  code->tree[lastnode].branches[0] = value;
  code->tree[lastnode].branches[1] = value;

  return (ARCHIVE_OK);
}