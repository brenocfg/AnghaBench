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
typedef  int /*<<< orphan*/  svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__db_base_remove (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_external_read (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_external_remove (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_remove_from_revision_control2 (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__external_remove(svn_wc_context_t *wc_ctx,
                        const char *wri_abspath,
                        const char *local_abspath,
                        svn_boolean_t declaration_only,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_node_kind_t kind;

  SVN_ERR(svn_wc__db_external_read(&status, &kind, NULL, NULL, NULL, NULL,
                                   NULL, NULL,
                                   wc_ctx->db, local_abspath, wri_abspath,
                                   scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_external_remove(wc_ctx->db, local_abspath, wri_abspath,
                                     NULL, scratch_pool));

  if (declaration_only)
    return SVN_NO_ERROR;

  if (kind == svn_node_dir)
    SVN_ERR(svn_wc_remove_from_revision_control2(wc_ctx, local_abspath,
                                                 TRUE, TRUE,
                                                 cancel_func, cancel_baton,
                                                 scratch_pool));
  else
    {
      SVN_ERR(svn_wc__db_base_remove(wc_ctx->db, local_abspath,
                                     FALSE, TRUE, FALSE,
                                     0,
                                     NULL, NULL, scratch_pool));
      SVN_ERR(svn_wc__wq_run(wc_ctx->db, local_abspath,
                             cancel_func, cancel_baton,
                             scratch_pool));
    }

  return SVN_NO_ERROR;
}