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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_node_check_replace (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 

svn_error_t *
svn_wc__node_get_commit_status(svn_boolean_t *added,
                               svn_boolean_t *deleted,
                               svn_boolean_t *is_replace_root,
                               svn_boolean_t *is_op_root,
                               svn_revnum_t *revision,
                               svn_revnum_t *original_revision,
                               const char **original_repos_relpath,
                               svn_wc_context_t *wc_ctx,
                               const char *local_abspath,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_boolean_t have_base;
  svn_boolean_t have_more_work;
  svn_boolean_t op_root;

  /* ### All of this should be handled inside a single read transaction */
  SVN_ERR(svn_wc__db_read_info(&status, NULL, revision, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               original_repos_relpath, NULL, NULL,
                               original_revision, NULL, NULL, NULL,
                               NULL, NULL,
                               &op_root, NULL, NULL,
                               &have_base, &have_more_work, NULL,
                               wc_ctx->db, local_abspath,
                               result_pool, scratch_pool));

  if (added)
    *added = (status == svn_wc__db_status_added);
  if (deleted)
    *deleted = (status == svn_wc__db_status_deleted);
  if (is_op_root)
    *is_op_root = op_root;

  if (is_replace_root)
    {
      if (status == svn_wc__db_status_added
          && op_root
          && (have_base || have_more_work))
        SVN_ERR(svn_wc__db_node_check_replace(is_replace_root, NULL, NULL,
                                              wc_ctx->db, local_abspath,
                                              scratch_pool));
      else
        *is_replace_root = FALSE;
    }

  /* Retrieve some information from BASE which is needed for replacing
     and/or deleting BASE nodes. */
  if (have_base
      && !have_more_work
      && op_root
      && (revision && !SVN_IS_VALID_REVNUM(*revision)))
    {
      SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, revision, NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL,
                                       wc_ctx->db, local_abspath,
                                       scratch_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}