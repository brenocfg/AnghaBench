#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_from_revision_status_callback ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__internal_remove_from_revision_control (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_walk_status (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_remove_from_revision_control2(svn_wc_context_t *wc_ctx,
                                    const char *local_abspath,
                                    svn_boolean_t destroy_wf,
                                    svn_boolean_t instant_error,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    apr_pool_t *scratch_pool)
{
  if (instant_error)
    {
      SVN_ERR(svn_wc_walk_status(wc_ctx, local_abspath, svn_depth_infinity,
                                 FALSE, FALSE, FALSE, NULL,
                                 remove_from_revision_status_callback, NULL,
                                 cancel_func, cancel_baton,
                                 scratch_pool));
    }
  return svn_error_trace(
      svn_wc__internal_remove_from_revision_control(wc_ctx->db,
                                                    local_abspath,
                                                    destroy_wf,
                                                    cancel_func,
                                                    cancel_baton,
                                                    scratch_pool));
}