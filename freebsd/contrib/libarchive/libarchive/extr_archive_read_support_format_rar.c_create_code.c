#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct huffman_code {int numentries; int /*<<< orphan*/  maxlength; int /*<<< orphan*/  minlength; scalar_t__ numallocatedentries; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 scalar_t__ add_value (struct archive_read*,struct huffman_code*,int,int,int) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ new_node (struct huffman_code*) ; 

__attribute__((used)) static int
create_code(struct archive_read *a, struct huffman_code *code,
            unsigned char *lengths, int numsymbols, char maxlength)
{
  int i, j, codebits = 0, symbolsleft = numsymbols;

  code->numentries = 0;
  code->numallocatedentries = 0;
  if (new_node(code) < 0) {
    archive_set_error(&a->archive, ENOMEM,
                      "Unable to allocate memory for node data.");
    return (ARCHIVE_FATAL);
  }
  code->numentries = 1;
  code->minlength = INT_MAX;
  code->maxlength = INT_MIN;
  codebits = 0;
  for(i = 1; i <= maxlength; i++)
  {
    for(j = 0; j < numsymbols; j++)
    {
      if (lengths[j] != i) continue;
      if (add_value(a, code, j, codebits, i) != ARCHIVE_OK)
        return (ARCHIVE_FATAL);
      codebits++;
      if (--symbolsleft <= 0) { break; break; }
    }
    codebits <<= 1;
  }
  return (ARCHIVE_OK);
}