#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_18__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_PROPERTIES_AVAILABLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* convert_to_working_status (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* svn_sqlite__column_checksum (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_token_null (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_row (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_read_pristine_info(svn_wc__db_status_t *status,
                              svn_node_kind_t *kind,
                              svn_revnum_t *changed_rev,
                              apr_time_t *changed_date,
                              const char **changed_author,
                              svn_depth_t *depth,  /* dirs only */
                              const svn_checksum_t **checksum, /* files only */
                              const char **target, /* symlinks only */
                              svn_boolean_t *had_props,
                              apr_hash_t **props,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  svn_error_t *err = NULL;
  int op_depth;
  svn_wc__db_status_t raw_status;
  svn_node_kind_t node_kind;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                                                local_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  /* Obtain the most likely to exist record first, to make sure we don't
     have to obtain the SQLite read-lock multiple times */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    {
      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND,
                               svn_sqlite__reset(stmt),
                               _("The node '%s' was not found."),
                               path_for_error_message(wcroot,
                                                      local_relpath,
                                                      scratch_pool));
    }

  op_depth = svn_sqlite__column_int(stmt, 0);
  raw_status = svn_sqlite__column_token(stmt, 3, presence_map);

  if (op_depth > 0 && raw_status == svn_wc__db_status_base_deleted)
    {
      SVN_ERR(svn_sqlite__step_row(stmt));

      op_depth = svn_sqlite__column_int(stmt, 0);
      raw_status = svn_sqlite__column_token(stmt, 3, presence_map);
    }

  node_kind = svn_sqlite__column_token(stmt, 4, kind_map);

  if (status)
    {
      if (op_depth > 0)
        {
          err = svn_error_compose_create(err,
                                         convert_to_working_status(
                                                    status,
                                                    raw_status));
        }
      else
        *status = raw_status;
    }
  if (kind)
    {
      *kind = node_kind;
    }
  if (changed_rev)
    {
      *changed_rev = svn_sqlite__column_revnum(stmt, 8);
    }
  if (changed_date)
    {
      *changed_date = svn_sqlite__column_int64(stmt, 9);
    }
  if (changed_author)
    {
      *changed_author = svn_sqlite__column_text(stmt, 10,
                                                result_pool);
    }
  if (depth)
    {
      if (node_kind != svn_node_dir)
        {
          *depth = svn_depth_unknown;
        }
      else
        {
          *depth = svn_sqlite__column_token_null(stmt, 11, depth_map,
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
          svn_error_t *err2;
          err2 = svn_sqlite__column_checksum(checksum, stmt, 6, result_pool);

          if (err2 != NULL)
            {
              if (err)
                err = svn_error_compose_create(
                         err,
                         svn_error_createf(
                               err->apr_err, err2,
                              _("The node '%s' has a corrupt checksum value."),
                              path_for_error_message(wcroot, local_relpath,
                                                     scratch_pool)));
              else
                err = err2;
            }
        }
    }
  if (target)
    {
      if (node_kind != svn_node_symlink)
        *target = NULL;
      else
        *target = svn_sqlite__column_text(stmt, 12, result_pool);
    }
  if (had_props)
    {
      *had_props = SQLITE_PROPERTIES_AVAILABLE(stmt, 14);
    }
  if (props)
    {
      if (raw_status == svn_wc__db_status_normal
          || raw_status == svn_wc__db_status_incomplete)
        {
          SVN_ERR(svn_sqlite__column_properties(props, stmt, 14,
                                                result_pool, scratch_pool));
          if (*props == NULL)
            *props = apr_hash_make(result_pool);
        }
      else
        {
          assert(svn_sqlite__column_is_null(stmt, 14));
          *props = NULL;
        }
    }

  return svn_error_trace(
            svn_error_compose_create(err,
                                     svn_sqlite__reset(stmt)));
}