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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_delta (int /*<<< orphan*/ *,char const*,scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ *) ; 

void
svn_txdelta__xdelta(svn_txdelta__ops_baton_t *build_baton,
                    const char *data,
                    apr_size_t source_len,
                    apr_size_t target_len,
                    apr_pool_t *pool)
{
  /*  We should never be asked to compute something when the source_len is 0;
      we just use a single insert op there (and rely on zlib for
      compression). */
  assert(source_len != 0);
  compute_delta(build_baton, data, source_len,
                data + source_len, target_len,
                pool);
}