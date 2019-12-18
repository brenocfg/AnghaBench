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
struct blocks {int dummy; } ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int MATCH_BLOCKSIZE ; 
 int NO_POSITION ; 
 int find_block (struct blocks const*,int /*<<< orphan*/  const,char const*) ; 
 int svn_cstring__match_length (char const*,char const*,int) ; 

__attribute__((used)) static apr_size_t
find_match(const struct blocks *blocks,
           const apr_uint32_t rolling,
           const char *a,
           apr_size_t asize,
           const char *b,
           apr_size_t bsize,
           apr_size_t *bposp,
           apr_size_t *aposp,
           apr_size_t pending_insert_start)
{
  apr_size_t apos, bpos = *bposp;
  apr_size_t delta, max_delta;

  apos = find_block(blocks, rolling, b + bpos);

  /* See if we have a match.  */
  if (apos == NO_POSITION)
    return 0;

  /* Extend the match forward as far as possible */
  max_delta = asize - apos - MATCH_BLOCKSIZE < bsize - bpos - MATCH_BLOCKSIZE
            ? asize - apos - MATCH_BLOCKSIZE
            : bsize - bpos - MATCH_BLOCKSIZE;
  delta = svn_cstring__match_length(a + apos + MATCH_BLOCKSIZE,
                                    b + bpos + MATCH_BLOCKSIZE,
                                    max_delta);

  /* See if we can extend backwards (max MATCH_BLOCKSIZE-1 steps because A's
     content has been sampled only every MATCH_BLOCKSIZE positions).  */
  while (apos > 0 && bpos > pending_insert_start && a[apos-1] == b[bpos-1])
    {
      --apos;
      --bpos;
      ++delta;
    }

  *aposp = apos;
  *bposp = bpos;

  return MATCH_BLOCKSIZE + delta;
}