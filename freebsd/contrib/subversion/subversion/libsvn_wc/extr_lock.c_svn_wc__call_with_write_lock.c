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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  (* svn_wc__with_write_lock_func_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__acquire_write_lock (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__release_write_lock (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__call_with_write_lock(svn_wc__with_write_lock_func_t func,
                             void *baton,
                             svn_wc_context_t *wc_ctx,
                             const char *local_abspath,
                             svn_boolean_t lock_anchor,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  svn_error_t *err1, *err2;
  const char *lock_root_abspath;

  SVN_ERR(svn_wc__acquire_write_lock(&lock_root_abspath, wc_ctx, local_abspath,
                                     lock_anchor, scratch_pool, scratch_pool));
  err1 = svn_error_trace(func(baton, result_pool, scratch_pool));
  err2 = svn_wc__release_write_lock(wc_ctx, lock_root_abspath, scratch_pool);
  return svn_error_compose_create(err1, err2);
}