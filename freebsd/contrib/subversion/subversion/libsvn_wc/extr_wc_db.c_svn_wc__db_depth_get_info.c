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
struct TYPE_12__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_13__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ SQLITE_PROPERTIES_AVAILABLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STMT_SELECT_DEPTH_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_working_status (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  repos_location_from_columns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__* svn_sqlite__column_checksum (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_token_null (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 

svn_error_t *
svn_wc__db_depth_get_info(svn_wc__db_status_t *status,
                          svn_node_kind_t *kind,
                          svn_revnum_t *revision,
                          const char **repos_relpath,
                          apr_int64_t *repos_id,
                          svn_revnum_t *changed_rev,
                          apr_time_t *changed_date,
                          const char **changed_author,
                          svn_depth_t *depth,
                          const svn_checksum_t **checksum,
                          const char **target,
                          svn_boolean_t *had_props,
                          apr_hash_t **props,
                          svn_wc__db_wcroot_t *wcroot,
                          const char *local_relpath,
                          int op_depth,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_DEPTH_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd",
                            wcroot->wc_id, local_relpath, op_depth));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (have_row)
    {
      svn_wc__db_status_t node_status = svn_sqlite__column_token(stmt, 2,
                                                                 presence_map);
      svn_node_kind_t node_kind = svn_sqlite__column_token(stmt, 3, kind_map);

      if (kind)
        {
          *kind = node_kind;
        }
      if (status)
        {
          *status = node_status;

          if (op_depth > 0)
            SVN_ERR(convert_to_working_status(status, *status));
        }
      repos_location_from_columns(repos_id, revision, repos_relpath,
                                  stmt, 0, 4, 1, result_pool);

      if (changed_rev)
        {
          *changed_rev = svn_sqlite__column_revnum(stmt, 7);
        }
      if (changed_date)
        {
          *changed_date = svn_sqlite__column_int64(stmt, 8);
        }
      if (changed_author)
        {
          /* Result may be NULL. */
          *changed_author = svn_sqlite__column_text(stmt, 9, result_pool);
        }
      if (depth)
        {
          if (node_kind != svn_node_dir)
            {
              *depth = svn_depth_unknown;
            }
          else
            {
              *depth = svn_sqlite__column_token_null(stmt, 10, depth_map,
                                                     svn_depth_unknown);
            }
        }
      if (checksum)
        {
          if (node_kind != svn_node_file)
            {
              *checksum = NULL;
            }
          else
            {
              err = svn_sqlite__column_checksum(checksum, stmt, 5,
                                                result_pool);
              if (err != NULL)
                err = svn_error_createf(
                        err->apr_err, err,
                        _("The node '%s' has a corrupt checksum value."),
                        path_for_error_message(wcroot, local_relpath,
                                               scratch_pool));
            }
        }
      if (target)
        {
          if (node_kind != svn_node_symlink)
            *target = NULL;
          else
            *target = svn_sqlite__column_text(stmt, 11, result_pool);
        }
      if (had_props)
        {
          *had_props = SQLITE_PROPERTIES_AVAILABLE(stmt, 12);
        }
      if (props)
        {
          if (node_status == svn_wc__db_status_normal
              || node_status == svn_wc__db_status_incomplete)
            {
              SVN_ERR(svn_sqlite__column_properties(props, stmt, 12,
                                                    result_pool, scratch_pool));
              if (*props == NULL)
                *props = apr_hash_make(result_pool);
            }
          else
            {
              assert(svn_sqlite__column_is_null(stmt, 12));
              *props = NULL;
            }
        }
    }
  else
    {
      err = svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                              _("The node '%s' was not found."),
                              path_for_error_message(wcroot, local_relpath,
                                                     scratch_pool));
    }

  /* Note: given the composition, no need to wrap for tracing.  */
  return svn_error_compose_create(err, svn_sqlite__reset(stmt));
}