#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_2__* convert_db_kind_to_node_kind (scalar_t__*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 char const* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 TYPE_2__* svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info (int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 134 
#define  svn_wc__db_status_deleted 133 
#define  svn_wc__db_status_excluded 132 
#define  svn_wc__db_status_incomplete 131 
#define  svn_wc__db_status_normal 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_state_missing ; 
 int /*<<< orphan*/  svn_wc_notify_state_obstructed ; 

svn_error_t *
svn_wc__check_for_obstructions(svn_wc_notify_state_t *obstruction_state,
                               svn_node_kind_t *kind,
                               svn_boolean_t *deleted,
                               svn_boolean_t *excluded,
                               svn_depth_t *parent_depth,
                               svn_wc_context_t *wc_ctx,
                               const char *local_abspath,
                               svn_boolean_t no_wcroot_check,
                               apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_node_kind_t db_kind;
  svn_node_kind_t disk_kind;
  svn_error_t *err;

  *obstruction_state = svn_wc_notify_state_inapplicable;
  if (kind)
    *kind = svn_node_none;
  if (deleted)
    *deleted = FALSE;
  if (excluded)
    *excluded = FALSE;
  if (parent_depth)
    *parent_depth = svn_depth_unknown;

  SVN_ERR(svn_io_check_path(local_abspath, &disk_kind, scratch_pool));

  err = svn_wc__db_read_info(&status, &db_kind, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL,
                             wc_ctx->db, local_abspath,
                             scratch_pool, scratch_pool);

  if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
    {
      svn_error_clear(err);

      if (disk_kind != svn_node_none)
        {
          /* Nothing in the DB, but something on disk */
          *obstruction_state = svn_wc_notify_state_obstructed;
          return SVN_NO_ERROR;
        }

      err = svn_wc__db_read_info(&status, &db_kind, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, parent_depth, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL,
                                 wc_ctx->db, svn_dirent_dirname(local_abspath,
                                                                scratch_pool),
                                 scratch_pool, scratch_pool);

      if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          svn_error_clear(err);
          /* No versioned parent; we can't add a node here */
          *obstruction_state = svn_wc_notify_state_obstructed;
          return SVN_NO_ERROR;
        }
      else
        SVN_ERR(err);

      if (db_kind != svn_node_dir
          || (status != svn_wc__db_status_normal
              && status != svn_wc__db_status_added))
        {
          /* The parent doesn't allow nodes to be added below it */
          *obstruction_state = svn_wc_notify_state_obstructed;
        }

      return SVN_NO_ERROR;
    }
  else
    SVN_ERR(err);

  /* Check for obstructing working copies */
  if (!no_wcroot_check
      && db_kind == svn_node_dir
      && status == svn_wc__db_status_normal)
    {
      svn_boolean_t is_root;
      SVN_ERR(svn_wc__db_is_wcroot(&is_root, wc_ctx->db, local_abspath,
                                   scratch_pool));

      if (is_root)
        {
          /* Callers should handle this as unversioned */
          *obstruction_state = svn_wc_notify_state_obstructed;
          return SVN_NO_ERROR;
        }
    }

  if (kind)
    SVN_ERR(convert_db_kind_to_node_kind(kind, db_kind, status, FALSE));

  switch (status)
    {
      case svn_wc__db_status_deleted:
        if (deleted)
          *deleted = TRUE;
        /* Fall through to svn_wc__db_status_not_present */
      case svn_wc__db_status_not_present:
        if (disk_kind != svn_node_none)
          *obstruction_state = svn_wc_notify_state_obstructed;
        break;

      case svn_wc__db_status_excluded:
      case svn_wc__db_status_server_excluded:
        if (excluded)
          *excluded = TRUE;
        /* fall through */
      case svn_wc__db_status_incomplete:
        *obstruction_state = svn_wc_notify_state_missing;
        break;

      case svn_wc__db_status_added:
      case svn_wc__db_status_normal:
        if (disk_kind == svn_node_none)
          *obstruction_state = svn_wc_notify_state_missing;
        else
          {
            svn_node_kind_t expected_kind;

            SVN_ERR(convert_db_kind_to_node_kind(&expected_kind, db_kind,
                                                 status, FALSE));

            if (disk_kind != expected_kind)
              *obstruction_state = svn_wc_notify_state_obstructed;
          }
        break;
      default:
        SVN_ERR_MALFUNCTION();
    }

  return SVN_NO_ERROR;
}