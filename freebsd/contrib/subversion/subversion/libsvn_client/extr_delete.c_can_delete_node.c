#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct can_delete_baton_t {char const* root_abspath; int /*<<< orphan*/  target_missing; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  find_undeletables ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_wc_get_default_ignores (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_walk_status (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct can_delete_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
can_delete_node(svn_boolean_t *target_missing,
                const char *local_abspath,
                svn_client_ctx_t *ctx,
                apr_pool_t *scratch_pool)
{
  apr_array_header_t *ignores;
  struct can_delete_baton_t cdt;

  /* Use an infinite-depth status check to see if there's anything in
     or under PATH which would make it unsafe for deletion.  The
     status callback function find_undeletables() makes the
     determination, returning an error if it finds anything that shouldn't
     be deleted. */

  SVN_ERR(svn_wc_get_default_ignores(&ignores, ctx->config, scratch_pool));

  cdt.root_abspath = local_abspath;
  cdt.target_missing = FALSE;

  SVN_ERR(svn_wc_walk_status(ctx->wc_ctx,
                             local_abspath,
                             svn_depth_infinity,
                             FALSE /* get_all */,
                             FALSE /* no_ignore */,
                             FALSE /* ignore_text_mod */,
                             ignores,
                             find_undeletables, &cdt,
                             ctx->cancel_func,
                             ctx->cancel_baton,
                             scratch_pool));

  if (target_missing)
    *target_missing = cdt.target_missing;

  return SVN_NO_ERROR;
}