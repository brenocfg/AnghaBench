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
typedef  int /*<<< orphan*/  svn_txdelta__ops_baton_t ;
struct blocks {int* flags; } ;
typedef  int apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int MATCH_BLOCKSIZE ; 
 int adler32_replace (int,char const,char const) ; 
 int find_match (struct blocks*,int,char const*,int,char const*,int,int*,int*,int) ; 
 size_t hash_flags (int) ; 
 int init_adler32 (char const*) ; 
 int /*<<< orphan*/  init_blocks_table (char const*,int,struct blocks*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_delta_trailer (int /*<<< orphan*/ *,char const*,int,char const*,int,int,int /*<<< orphan*/ *) ; 
 int svn_cstring__match_length (char const*,char const*,int) ; 
 int svn_cstring__reverse_match_length (char const*,char const*,int) ; 
 int /*<<< orphan*/  svn_txdelta__insert_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ *) ; 
 int svn_txdelta__remove_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_txdelta_new ; 
 int /*<<< orphan*/  svn_txdelta_source ; 

__attribute__((used)) static void
compute_delta(svn_txdelta__ops_baton_t *build_baton,
              const char *a,
              apr_size_t asize,
              const char *b,
              apr_size_t bsize,
              apr_pool_t *pool)
{
  struct blocks blocks;
  apr_uint32_t rolling;
  apr_size_t lo = 0, pending_insert_start = 0, upper;

  /* Optimization: directly compare window starts. If more than 4
   * bytes match, we can immediately create a matching windows.
   * Shorter sequences result in a net data increase. */
  lo = svn_cstring__match_length(a, b, asize > bsize ? bsize : asize);
  if ((lo > 4) || (lo == bsize))
    {
      svn_txdelta__insert_op(build_baton, svn_txdelta_source,
                             0, lo, NULL, pool);
      pending_insert_start = lo;
    }
  else
    lo = 0;

  /* If the size of the target is smaller than the match blocksize, just
     insert the entire target.  */
  if ((bsize - lo < MATCH_BLOCKSIZE) || (asize < MATCH_BLOCKSIZE))
    {
      store_delta_trailer(build_baton, a, asize, b, bsize, lo, pool);
      return;
    }

  upper = bsize - MATCH_BLOCKSIZE; /* this is now known to be >= LO */

  /* Initialize the matches table.  */
  init_blocks_table(a, asize, &blocks, pool);

  /* Initialize our rolling checksum.  */
  rolling = init_adler32(b + lo);
  while (lo < upper)
    {
      apr_size_t matchlen;
      apr_size_t apos;

      /* Quickly skip positions whose respective ROLLING checksums
         definitely do not match any SLOT in BLOCKS. */
      while (!(blocks.flags[hash_flags(rolling)] & (1 << (rolling & 7)))
             && lo < upper)
        {
          rolling = adler32_replace(rolling, b[lo], b[lo+MATCH_BLOCKSIZE]);
          lo++;
        }

      /* LO is still <= UPPER, i.e. the following lookup is legal:
         Closely check whether we've got a match for the current location.
         Due to the above pre-filter, chances are that we find one. */
      matchlen = find_match(&blocks, rolling, a, asize, b, bsize,
                            &lo, &apos, pending_insert_start);

      /* If we didn't find a real match, insert the byte at the target
         position into the pending insert.  */
      if (matchlen == 0)
        {
          /* move block one position forward. Short blocks at the end of
             the buffer cannot be used as the beginning of a new match */
          if (lo + MATCH_BLOCKSIZE < bsize)
            rolling = adler32_replace(rolling, b[lo], b[lo+MATCH_BLOCKSIZE]);

          lo++;
        }
      else
        {
          /* store the sequence of B that is between the matches */
          if (lo - pending_insert_start > 0)
            svn_txdelta__insert_op(build_baton, svn_txdelta_new,
                                   0, lo - pending_insert_start,
                                   b + pending_insert_start, pool);
          else
            {
              /* the match borders on the previous op. Maybe, we found a
               * match that is better than / overlapping the previous one. */
              apr_size_t len = svn_cstring__reverse_match_length
                                 (a + apos, b + lo, apos < lo ? apos : lo);
              if (len > 0)
                {
                  len = svn_txdelta__remove_copy(build_baton, len);
                  apos -= len;
                  matchlen += len;
                  lo -= len;
                }
            }

          /* Reset the pending insert start to immediately after the
             match. */
          lo += matchlen;
          pending_insert_start = lo;
          svn_txdelta__insert_op(build_baton, svn_txdelta_source,
                                 apos, matchlen, NULL, pool);

          /* Calculate the Adler32 sum for the first block behind the match.
           * Ignore short buffers at the end of B.
           */
          if (lo + MATCH_BLOCKSIZE <= bsize)
            rolling = init_adler32(b + lo);
        }
    }

  /* If we still have an insert pending at the end, throw it in.  */
  store_delta_trailer(build_baton, a, asize, b, bsize, pending_insert_start, pool);
}