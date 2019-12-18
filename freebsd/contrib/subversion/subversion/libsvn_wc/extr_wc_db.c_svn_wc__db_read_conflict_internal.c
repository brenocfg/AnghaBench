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
struct TYPE_4__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  void* svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STMT_SELECT_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * convert_to_working_status (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 void* svn_node_none ; 
 int /*<<< orphan*/ * svn_skel__parse (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 void* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__column_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 

svn_error_t *
svn_wc__db_read_conflict_internal(svn_skel_t **conflict,
                                  svn_node_kind_t *kind,
                                  apr_hash_t **props,
                                  svn_wc__db_wcroot_t *wcroot,
                                  const char *local_relpath,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  if (kind)
    *kind = svn_node_none;
  if (props)
    *props = NULL;

  /* Check if we have a conflict in ACTUAL */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ACTUAL_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (have_row)
    {
      apr_size_t cfl_len;
      const void *cfl_data;

      /* svn_skel__parse doesn't copy data, so store in result_pool */
      cfl_data = svn_sqlite__column_blob(stmt, 2, &cfl_len, result_pool);

      if (cfl_data)
        *conflict = svn_skel__parse(cfl_data, cfl_len, result_pool);
      else
        *conflict = NULL;

      if (props)
        {
          svn_error_t *err;

          err = svn_error_trace(svn_sqlite__column_properties(props, stmt, 1,
                                                              result_pool,
                                                              scratch_pool));

          if (err)
            return svn_error_compose_create(err, svn_sqlite__reset(stmt));
        }
    }
  else
    *conflict = NULL;

  SVN_ERR(svn_sqlite__reset(stmt));

  if (!have_row || kind || (props && !*props))
    {
      svn_error_t *err = NULL;
      svn_boolean_t have_info = FALSE;

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_NODE_INFO));

      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id,
                                local_relpath));

      SVN_ERR(svn_sqlite__step(&have_info, stmt));

      if (have_info)
        {
          if (kind)
            {
              svn_wc__db_status_t status;
              int op_depth = svn_sqlite__column_int(stmt, 0);

              status = svn_sqlite__column_token(stmt, 3, presence_map);

              if (op_depth > 0)
                err = convert_to_working_status(&status, status);

              if (!err && (status == svn_wc__db_status_normal
                           || status == svn_wc__db_status_added
                           || status == svn_wc__db_status_deleted
                           || status == svn_wc__db_status_incomplete))
                {
                  *kind = svn_sqlite__column_token(stmt, 4, kind_map);
                }
            }

          /* Need props, and no props in ACTUAL? */
          if (!err && (props && !*props))
            {
              err = svn_sqlite__column_properties(props, stmt, 14,
                                                  result_pool, scratch_pool);
            }
        }

      SVN_ERR(svn_error_compose_create(err, svn_sqlite__reset(stmt)));

      if (!have_row && !have_info)
        {
          return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                   _("The node '%s' was not found."),
                                   path_for_error_message(wcroot,
                                                          local_relpath,
                                                          scratch_pool));
        }
    }

  return SVN_NO_ERROR;
}