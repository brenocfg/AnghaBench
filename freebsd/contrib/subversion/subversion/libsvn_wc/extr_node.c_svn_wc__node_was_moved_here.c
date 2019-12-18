#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_wc__db_scan_moved (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__node_was_moved_here(const char **moved_from_abspath,
                            const char **delete_op_root_abspath,
                            svn_wc_context_t *wc_ctx,
                            const char *local_abspath,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  if (moved_from_abspath)
    *moved_from_abspath = NULL;
  if (delete_op_root_abspath)
    *delete_op_root_abspath = NULL;

  err = svn_wc__db_scan_moved(moved_from_abspath, NULL, NULL,
                              delete_op_root_abspath,
                              wc_ctx->db, local_abspath,
                              result_pool, scratch_pool);

  if (err)
    {
      /* Return error for not added nodes */
      if (err->apr_err != SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
        return svn_error_trace(err);

      /* Path not moved here */
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }

  return SVN_NO_ERROR;
}