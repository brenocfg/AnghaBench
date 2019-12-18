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
struct blocks {int max; char const* data; int /*<<< orphan*/  flags; TYPE_1__* slots; } ;
typedef  int apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  pos; scalar_t__ adlersum; } ;

/* Variables and functions */
 int MATCH_BLOCKSIZE ; 
 int /*<<< orphan*/  NO_POSITION ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  add_block (struct blocks*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_adler32 (char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_blocks_table(const char *data,
                  apr_size_t datalen,
                  struct blocks *blocks,
                  apr_pool_t *pool)
{
  apr_size_t nblocks;
  apr_size_t wnslots = 1;
  apr_uint32_t nslots;
  apr_uint32_t i;

  /* Be pessimistic about the block count. */
  nblocks = datalen / MATCH_BLOCKSIZE + 1;
  /* Find nearest larger power of two. */
  while (wnslots <= nblocks)
    wnslots *= 2;
  /* Double the number of slots to avoid a too high load. */
  wnslots *= 2;
  /* Narrow the number of slots to 32 bits, which is the size of the
     block position index in the hash table.
     Sanity check: On 64-bit platforms, apr_size_t is likely to be
     larger than apr_uint32_t. Make sure that the number of slots
     actually fits into blocks->max.  It's safe to use a hard assert
     here, because the largest possible value for nslots is
     proportional to the text delta window size and is therefore much
     smaller than the range of an apr_uint32_t.  If we ever happen to
     increase the window size too much, this assertion will get
     triggered by the test suite. */
  nslots = (apr_uint32_t) wnslots;
  SVN_ERR_ASSERT_NO_RETURN(wnslots == nslots);
  blocks->max = nslots - 1;
  blocks->data = data;
  blocks->slots = apr_palloc(pool, nslots * sizeof(*(blocks->slots)));
  for (i = 0; i < nslots; ++i)
    {
      /* Avoid using an indeterminate value in the lookup. */
      blocks->slots[i].adlersum = 0;
      blocks->slots[i].pos = NO_POSITION;
    }

  /* No checksum entries in SLOTS, yet => reset all checksum flags. */
  memset(blocks->flags, 0, sizeof(blocks->flags));

  /* If there is an odd block at the end of the buffer, we will
     not use that shorter block for deltification (only indirectly
     as an extension of some previous block). */
  for (i = 0; i + MATCH_BLOCKSIZE <= datalen; i += MATCH_BLOCKSIZE)
    add_block(blocks, init_adler32(data + i), i);
}