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
typedef  int /*<<< orphan*/  svn_wc_status_func_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct old_status_func_cb_baton {void* original_baton; int /*<<< orphan*/  original_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct old_status_func_cb_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  old_status_func_cb ; 
 int /*<<< orphan*/ * svn_client_status2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct old_status_func_cb_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_status(svn_revnum_t *result_rev,
                  const char *path,
                  svn_opt_revision_t *revision,
                  svn_wc_status_func_t status_func,
                  void *status_baton,
                  svn_boolean_t recurse,
                  svn_boolean_t get_all,
                  svn_boolean_t update,
                  svn_boolean_t no_ignore,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *pool)
{
  struct old_status_func_cb_baton *b = apr_pcalloc(pool, sizeof(*b));
  b->original_func = status_func;
  b->original_baton = status_baton;

  return svn_client_status2(result_rev, path, revision,
                            old_status_func_cb, b,
                            recurse, get_all, update, no_ignore, FALSE,
                            ctx, pool);
}