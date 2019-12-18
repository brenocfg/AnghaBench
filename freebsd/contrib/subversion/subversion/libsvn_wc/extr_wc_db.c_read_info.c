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
typedef  void* svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
struct TYPE_18__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  void* svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  INVALID_REPOS_ID ; 
 int SQLITE_PROPERTIES_AVAILABLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STMT_SELECT_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO_WITH_LOCK ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int*) ; 
 scalar_t__ SVN_ERR_WC_CORRUPT ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* column_token_err (TYPE_2__**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_working_status (void**,void*) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  get_recorded_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/ * lock_from_columns (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  repos_location_from_columns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 void* svn_depth_unknown ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_quick_wrapf (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 scalar_t__ svn_node_unknown ; 
 TYPE_2__* svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__column_checksum (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 void* svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
read_info(svn_wc__db_status_t *status,
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
          const char **original_repos_relpath,
          apr_int64_t *original_repos_id,
          svn_revnum_t *original_revision,
          svn_wc__db_lock_t **lock,
          svn_filesize_t *recorded_size,
          apr_time_t *recorded_time,
          const char **changelist,
          svn_boolean_t *conflicted,
          svn_boolean_t *op_root,
          svn_boolean_t *had_props,
          svn_boolean_t *props_mod,
          svn_boolean_t *have_base,
          svn_boolean_t *have_more_work,
          svn_boolean_t *have_work,
          svn_wc__db_wcroot_t *wcroot,
          const char *local_relpath,
          apr_pool_t *result_pool,
          apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt_info;
  svn_sqlite__stmt_t *stmt_act;
  svn_boolean_t have_info;
  svn_boolean_t have_act;
  svn_error_t *err = NULL;

  /* Obtain the most likely to exist record first, to make sure we don't
     have to obtain the SQLite read-lock multiple times */
  SVN_ERR(svn_sqlite__get_statement(&stmt_info, wcroot->sdb,
                                    lock ? STMT_SELECT_NODE_INFO_WITH_LOCK
                                         : STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt_info, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_info, stmt_info));

  if (changelist || conflicted || props_mod)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt_act, wcroot->sdb,
                                        STMT_SELECT_ACTUAL_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt_act, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step(&have_act, stmt_act));
    }
  else
    {
      have_act = FALSE;
      stmt_act = NULL;
    }

  if (have_info)
    {
      int op_depth;
      svn_node_kind_t node_kind;

      op_depth = svn_sqlite__column_int(stmt_info, 0);
      node_kind = column_token_err(&err, stmt_info, 4, kind_map);

      if (status)
        {
          *status = column_token_err(&err, stmt_info, 3, presence_map);

          if (op_depth != 0) /* WORKING */
            err = svn_error_compose_create(err,
                                           convert_to_working_status(status,
                                                                     *status));
        }
      if (kind)
        {
          *kind = node_kind;
        }
      if (op_depth != 0)
        {
          if (repos_id)
            *repos_id = INVALID_REPOS_ID;
          if (revision)
            *revision = SVN_INVALID_REVNUM;
          if (repos_relpath)
            /* Our path is implied by our parent somewhere up the tree.
               With the NULL value and status, the caller will know to
               search up the tree for the base of our path.  */
            *repos_relpath = NULL;
        }
      else
        {
          /* Fetch repository information. If we have a
             WORKING_NODE (and have been added), then the repository
             we're being added to will be dependent upon a parent. The
             caller can scan upwards to locate the repository.  */
          repos_location_from_columns(repos_id, revision, repos_relpath,
                                      stmt_info, 1, 5, 2, result_pool);
        }
      if (changed_rev)
        {
          *changed_rev = svn_sqlite__column_revnum(stmt_info, 8);
        }
      if (changed_date)
        {
          *changed_date = svn_sqlite__column_int64(stmt_info, 9);
        }
      if (changed_author)
        {
          *changed_author = svn_sqlite__column_text(stmt_info, 10,
                                                    result_pool);
        }
      if (recorded_time)
        {
          *recorded_time = svn_sqlite__column_int64(stmt_info, 13);
        }
      if (depth)
        {
          if (node_kind != svn_node_dir)
            *depth = svn_depth_unknown;
          else if (svn_sqlite__column_is_null(stmt_info, 11))
            *depth = svn_depth_unknown;
          else
            *depth = column_token_err(&err, stmt_info, 11, depth_map);
        }
      if (checksum)
        {
          if (node_kind != svn_node_file)
            {
              *checksum = NULL;
            }
          else
            {

              err = svn_error_compose_create(
                        err, svn_sqlite__column_checksum(checksum, stmt_info, 6,
                                                         result_pool));
            }
        }
      if (recorded_size)
        {
          *recorded_size = get_recorded_size(stmt_info, 7);
        }
      if (target)
        {
          if (node_kind != svn_node_symlink)
            *target = NULL;
          else
            *target = svn_sqlite__column_text(stmt_info, 12, result_pool);
        }
      if (changelist)
        {
          if (have_act)
            *changelist = svn_sqlite__column_text(stmt_act, 0, result_pool);
          else
            *changelist = NULL;
        }
      if (op_depth == 0)
        {
          if (original_repos_id)
            *original_repos_id = INVALID_REPOS_ID;
          if (original_revision)
            *original_revision = SVN_INVALID_REVNUM;
          if (original_repos_relpath)
            *original_repos_relpath = NULL;
        }
      else
        {
          repos_location_from_columns(original_repos_id,
                                      original_revision,
                                      original_repos_relpath,
                                      stmt_info, 1, 5, 2, result_pool);
        }
      if (props_mod)
        {
          *props_mod = have_act && !svn_sqlite__column_is_null(stmt_act, 1);
        }
      if (had_props)
        {
          *had_props = SQLITE_PROPERTIES_AVAILABLE(stmt_info, 14);
        }
      if (conflicted)
        {
          if (have_act)
            {
              *conflicted =
                 !svn_sqlite__column_is_null(stmt_act, 2); /* conflict_data */
            }
          else
            *conflicted = FALSE;
        }

      if (lock)
        {
          if (op_depth != 0)
            *lock = NULL;
          else
            *lock = lock_from_columns(stmt_info, 17, 18, 19, 20, result_pool);
        }

      if (have_work)
        *have_work = (op_depth != 0);

      if (op_root)
        {
          *op_root = ((op_depth > 0)
                      && (op_depth == relpath_depth(local_relpath)));
        }

      if (have_base || have_more_work)
        {
          if (have_more_work)
            *have_more_work = FALSE;

          while (!err && op_depth != 0)
            {
              err = svn_sqlite__step(&have_info, stmt_info);

              if (err || !have_info)
                break;

              op_depth = svn_sqlite__column_int(stmt_info, 0);

              if (have_more_work)
                {
                  if (op_depth > 0)
                    *have_more_work = TRUE;

                  if (!have_base)
                   break;
                }
            }

          if (have_base)
            *have_base = (op_depth == 0);
        }
    }
  else if (have_act)
    {
      /* A row in ACTUAL_NODE should never exist without a corresponding
         node in BASE_NODE and/or WORKING_NODE unless it flags a tree conflict. */
      if (svn_sqlite__column_is_null(stmt_act, 2)) /* conflict_data */
          err = svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                                  _("Corrupt data for '%s'"),
                                  path_for_error_message(wcroot, local_relpath,
                                                         scratch_pool));
      /* ### What should we return?  Should we have a separate
             function for reading actual-only nodes? */

      /* As a safety measure, until we decide if we want to use
         read_info for actual-only nodes, make sure the caller asked
         for the conflict status. */
      SVN_ERR_ASSERT(conflicted);

      if (status)
        *status = svn_wc__db_status_normal;  /* What! No it's not! */
      if (kind)
        *kind = svn_node_unknown;
      if (revision)
        *revision = SVN_INVALID_REVNUM;
      if (repos_relpath)
        *repos_relpath = NULL;
      if (repos_id)
        *repos_id = INVALID_REPOS_ID;
      if (changed_rev)
        *changed_rev = SVN_INVALID_REVNUM;
      if (changed_date)
        *changed_date = 0;
      if (depth)
        *depth = svn_depth_unknown;
      if (checksum)
        *checksum = NULL;
      if (target)
        *target = NULL;
      if (original_repos_relpath)
        *original_repos_relpath = NULL;
      if (original_repos_id)
        *original_repos_id = INVALID_REPOS_ID;
      if (original_revision)
        *original_revision = SVN_INVALID_REVNUM;
      if (lock)
        *lock = NULL;
      if (recorded_size)
        *recorded_size = 0;
      if (recorded_time)
        *recorded_time = 0;
      if (changelist)
        *changelist = svn_sqlite__column_text(stmt_act, 0, result_pool);
      if (op_root)
        *op_root = FALSE;
      if (had_props)
        *had_props = FALSE;
      if (props_mod)
        *props_mod = FALSE;
      if (conflicted)
        *conflicted = TRUE;
      if (have_base)
        *have_base = FALSE;
      if (have_more_work)
        *have_more_work = FALSE;
      if (have_work)
        *have_work = FALSE;
    }
  else
    {
      err = svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                              _("The node '%s' was not found."),
                              path_for_error_message(wcroot, local_relpath,
                                                     scratch_pool));
    }

  if (stmt_act != NULL)
    err = svn_error_compose_create(err, svn_sqlite__reset(stmt_act));

  if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
    err = svn_error_quick_wrapf(err, _("Error reading node '%s'"),
                                local_relpath);

  SVN_ERR(svn_error_compose_create(err, svn_sqlite__reset(stmt_info)));

  return SVN_NO_ERROR;
}