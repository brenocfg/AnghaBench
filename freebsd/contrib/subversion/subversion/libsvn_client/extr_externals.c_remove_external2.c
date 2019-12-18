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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc__external_remove (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
remove_external2(svn_boolean_t *removed,
                svn_wc_context_t *wc_ctx,
                const char *wri_abspath,
                const char *local_abspath,
                svn_node_kind_t external_kind,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *scratch_pool)
{
  SVN_ERR(svn_wc__external_remove(wc_ctx, wri_abspath,
                                  local_abspath,
                                  (external_kind == svn_node_none),
                                  cancel_func, cancel_baton,
                                  scratch_pool));

  *removed = TRUE;
  return SVN_NO_ERROR;
}