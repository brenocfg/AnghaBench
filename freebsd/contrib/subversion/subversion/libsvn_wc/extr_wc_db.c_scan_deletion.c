#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_DELETION_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_moved_to (char const**,char const**,int*,int /*<<< orphan*/ *,char const*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 
 scalar_t__ svn_wc__db_status_not_present ; 

__attribute__((used)) static svn_error_t *
scan_deletion(const char **base_del_relpath,
              const char **moved_to_relpath,
              const char **work_del_relpath,
              const char **moved_to_op_root_relpath,
              svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  const char *current_relpath = local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_wc__db_status_t work_presence;
  svn_boolean_t have_row, scan, have_base;
  int op_depth;

  /* Initialize all the OUT parameters.  */
  if (base_del_relpath != NULL)
    *base_del_relpath = NULL;
  if (moved_to_relpath != NULL)
    *moved_to_relpath = NULL;
  if (work_del_relpath != NULL)
    *work_del_relpath = NULL;
  if (moved_to_op_root_relpath != NULL)
    *moved_to_op_root_relpath = NULL;

  /* If looking for moved-to info then we need to scan every path
     until we find it.  If not looking for moved-to we only need to
     check op-roots and parents of op-roots. */
  scan = (moved_to_op_root_relpath || moved_to_relpath);

  SVN_ERR(svn_sqlite__get_statement(
                    &stmt, wcroot->sdb, STMT_SELECT_DELETION_INFO));

  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, current_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (!have_row)
    return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, svn_sqlite__reset(stmt),
                             _("The node '%s' was not found."),
                             path_for_error_message(wcroot, local_relpath,
                                                    scratch_pool));

  work_presence = svn_sqlite__column_token(stmt, 1, presence_map);
  have_base = !svn_sqlite__column_is_null(stmt, 0);
  if (work_presence != svn_wc__db_status_not_present
      && work_presence != svn_wc__db_status_base_deleted)
    return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS,
                             svn_sqlite__reset(stmt),
                             _("Expected node '%s' to be deleted."),
                             path_for_error_message(wcroot, local_relpath,
                                                    scratch_pool));

  op_depth = svn_sqlite__column_int(stmt, 2);

  /* Special case: LOCAL_RELPATH not-present within a WORKING tree, we
     treat this as an op-root.  At commit time we need to explicitly
     delete such nodes otherwise they will be present in the
     repository copy. */
  if (work_presence == svn_wc__db_status_not_present
      && work_del_relpath && !*work_del_relpath)
    {
      *work_del_relpath = apr_pstrdup(result_pool, current_relpath);

      if (!scan && !base_del_relpath)
        {
          /* We have all we need, exit early */
          SVN_ERR(svn_sqlite__reset(stmt));
          return SVN_NO_ERROR;
        }
    }


  while (TRUE)
    {
      svn_error_t *err;
      const char *parent_relpath;
      int current_depth = relpath_depth(current_relpath);

      /* Step CURRENT_RELPATH to op-root */

      while (TRUE)
        {
          if (scan)
            {
              err = get_moved_to(moved_to_relpath, moved_to_op_root_relpath,
                                 &scan, stmt, current_relpath,
                                 wcroot, local_relpath,
                                 result_pool, scratch_pool);
              if (err || (!scan
                          && !base_del_relpath
                          && !work_del_relpath))
                {
                  /* We have all we need (or an error occurred) */
                  SVN_ERR(svn_sqlite__reset(stmt));
                  return svn_error_trace(err);
                }
            }

          if (current_depth <= op_depth)
            break;

          current_relpath = svn_relpath_dirname(current_relpath, scratch_pool);
          --current_depth;

          if (scan || current_depth == op_depth)
            {
              SVN_ERR(svn_sqlite__reset(stmt));
              SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id,
                                        current_relpath));
              SVN_ERR(svn_sqlite__step(&have_row, stmt));
              SVN_ERR_ASSERT(have_row);
              have_base = !svn_sqlite__column_is_null(stmt, 0);
            }
        }
      SVN_ERR(svn_sqlite__reset(stmt));

      /* Now CURRENT_RELPATH is an op-root, have a look at the parent. */

      SVN_ERR_ASSERT(current_relpath[0] != '\0'); /* Catch invalid data */
      parent_relpath = svn_relpath_dirname(current_relpath, scratch_pool);
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, parent_relpath));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      if (!have_row)
        {
          /* No row means no WORKING node which mean we just fell off
             the WORKING tree, so CURRENT_RELPATH is the op-root
             closest to the wc root. */
          if (have_base && base_del_relpath)
            *base_del_relpath = apr_pstrdup(result_pool, current_relpath);
          break;
        }

      /* Still in the WORKING tree so the first time we get here
         CURRENT_RELPATH is a delete op-root in the WORKING tree. */
      if (work_del_relpath && !*work_del_relpath)
        {
          *work_del_relpath = apr_pstrdup(result_pool, current_relpath);

          if (!scan && !base_del_relpath)
            break; /* We have all we need */
        }

      current_relpath = parent_relpath;
      op_depth = svn_sqlite__column_int(stmt, 2);
      have_base = !svn_sqlite__column_is_null(stmt, 0);
    }

  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}