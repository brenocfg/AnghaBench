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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ svn_cstring__reverse_match_length (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_txdelta__insert_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_new ; 
 int /*<<< orphan*/  svn_txdelta_source ; 

__attribute__((used)) static void
store_delta_trailer(svn_txdelta__ops_baton_t *build_baton,
                    const char *a,
                    apr_size_t asize,
                    const char *b,
                    apr_size_t bsize,
                    apr_size_t start,
                    apr_pool_t *pool)
{
  apr_size_t end_match;
  apr_size_t max_len = asize > (bsize - start) ? bsize - start : asize;
  if (max_len == 0)
    return;

  end_match = svn_cstring__reverse_match_length(a + asize, b + bsize,
                                                max_len);
  if (end_match <= 4)
    end_match = 0;

  if (bsize - start > end_match)
    svn_txdelta__insert_op(build_baton, svn_txdelta_new,
                           start, bsize - start - end_match, b + start, pool);
  if (end_match)
    svn_txdelta__insert_op(build_baton, svn_txdelta_source,
                           asize - end_match, end_match, NULL, pool);
}