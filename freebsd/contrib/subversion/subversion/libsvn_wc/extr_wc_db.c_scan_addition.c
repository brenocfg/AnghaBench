#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_SELECT_WORKING_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_moved_from_info (char const**,char const**,char const*,int*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_prefix (char const*,int,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_copied ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_moved_here ; 
 scalar_t__ svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
scan_addition(svn_wc__db_status_t *status,
              const char **op_root_relpath_p,
              const char **repos_relpath,
              apr_int64_t *repos_id,
              const char **original_repos_relpath,
              apr_int64_t *original_repos_id,
              svn_revnum_t *original_revision,
              const char **moved_from_relpath,
              const char **moved_from_op_root_relpath,
              int *moved_from_op_depth,
              svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  const char *op_root_relpath;
  const char *build_relpath = "";

  /* Initialize most of the OUT parameters. Generally, we'll only be filling
     in a subset of these, so it is easier to init all up front. Note that
     the STATUS parameter will be initialized once we read the status of
     the specified node.  */
  if (op_root_relpath_p)
    *op_root_relpath_p = NULL;
  if (original_repos_relpath)
    *original_repos_relpath = NULL;
  if (original_repos_id)
    *original_repos_id = INVALID_REPOS_ID;
  if (original_revision)
    *original_revision = SVN_INVALID_REVNUM;
  if (moved_from_relpath)
    *moved_from_relpath = NULL;
  if (moved_from_op_root_relpath)
    *moved_from_op_root_relpath = NULL;
  if (moved_from_op_depth)
    *moved_from_op_depth = 0;

  {
    svn_sqlite__stmt_t *stmt;
    svn_boolean_t have_row;
    svn_wc__db_status_t presence;
    int op_depth;
    const char *repos_prefix_path;

    /* ### is it faster to fetch fewer columns? */
    SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                      STMT_SELECT_WORKING_NODE));
    SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
    SVN_ERR(svn_sqlite__step(&have_row, stmt));

    if (!have_row)
      {
        /* Reset statement before returning */
        SVN_ERR(svn_sqlite__reset(stmt));

        /* ### maybe we should return a usage error instead?  */
        return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                 _("The node '%s' was not found."),
                                 path_for_error_message(wcroot,
                                                        local_relpath,
                                                        scratch_pool));
      }

    presence = svn_sqlite__column_token(stmt, 1, presence_map);

    /* The starting node should exist normally.  */
    op_depth = svn_sqlite__column_int(stmt, 0);
    if (op_depth == 0 || (presence != svn_wc__db_status_normal
                          && presence != svn_wc__db_status_incomplete))
      /* reset the statement as part of the error generation process */
      return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS,
                               svn_sqlite__reset(stmt),
                               _("Expected node '%s' to be added."),
                               path_for_error_message(wcroot,
                                                      local_relpath,
                                                      scratch_pool));

    if (original_revision)
      *original_revision = svn_sqlite__column_revnum(stmt, 12);

    /* Provide the default status; we'll override as appropriate. */
    if (status)
      {
        if (presence == svn_wc__db_status_normal)
          *status = svn_wc__db_status_added;
        else
          *status = svn_wc__db_status_incomplete;
      }


    /* Calculate the op root local path components */
    op_root_relpath = svn_relpath_prefix(local_relpath, op_depth,
                                         scratch_pool);
    repos_prefix_path = svn_relpath_skip_ancestor(op_root_relpath,
                                                  local_relpath);

    if (op_root_relpath_p)
      *op_root_relpath_p = apr_pstrdup(result_pool, op_root_relpath);

    /* ### This if-statement is quite redundant.
     * ### We're checking all these values again within the body anyway.
     * ### The body should be broken up appropriately and move into the
     * ### outer scope. */
    if (original_repos_relpath
        || original_repos_id
        || (original_revision
                && *original_revision == SVN_INVALID_REVNUM)
        || status
        || moved_from_relpath || moved_from_op_root_relpath)
      {
        if (local_relpath != op_root_relpath)
          /* requery to get the add/copy root */
          {
            SVN_ERR(svn_sqlite__reset(stmt));

            SVN_ERR(svn_sqlite__bindf(stmt, "is",
                                      wcroot->wc_id, op_root_relpath));
            SVN_ERR(svn_sqlite__step(&have_row, stmt));

            if (!have_row)
              {
                /* Reset statement before returning */
                SVN_ERR(svn_sqlite__reset(stmt));

                /* ### maybe we should return a usage error instead?  */
                return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                         _("The node '%s' was not found."),
                                         path_for_error_message(wcroot,
                                                                op_root_relpath,
                                                                scratch_pool));
              }

            if (original_revision
                    && *original_revision == SVN_INVALID_REVNUM)
              *original_revision = svn_sqlite__column_revnum(stmt, 12);
          }

        if (original_repos_relpath)
          *original_repos_relpath = svn_sqlite__column_text(stmt, 11,
                                                            result_pool);

        if (!svn_sqlite__column_is_null(stmt, 10)
            && (status
                || original_repos_id
                || moved_from_relpath || moved_from_op_root_relpath))
          /* If column 10 (original_repos_id) is NULL,
             this is a plain add, not a copy or a move */
          {
            svn_boolean_t moved_here;
            if (original_repos_id)
              *original_repos_id = svn_sqlite__column_int64(stmt, 10);

            moved_here = svn_sqlite__column_boolean(stmt, 13 /* moved_here */);
            if (status)
              *status = moved_here ? svn_wc__db_status_moved_here
                                   : svn_wc__db_status_copied;

            if (moved_here
                && (moved_from_relpath || moved_from_op_root_relpath))
              {
                svn_error_t *err;

                err = get_moved_from_info(moved_from_relpath,
                                          moved_from_op_root_relpath,
                                          op_root_relpath,
                                          moved_from_op_depth,
                                          wcroot, local_relpath,
                                          result_pool,
                                          scratch_pool);

                if (err)
                  return svn_error_compose_create(
                                err, svn_sqlite__reset(stmt));
              }
          }
      }


    /* ### This loop here is to skip up to the first node which is a BASE node,
       because base_get_info() doesn't accommodate the scenario that
       we're looking at here; we found the true op_root, which may be inside
       further changed trees. */
    if (repos_relpath || repos_id)
      {
        const char *base_relpath;

        while (TRUE)
          {
            const char *tmp;

            SVN_ERR(svn_sqlite__reset(stmt));

            /* Pointing at op_depth, look at the parent */
            repos_prefix_path =
                svn_relpath_join(svn_relpath_basename(op_root_relpath, NULL),
                                 repos_prefix_path,
                                 scratch_pool);
            op_root_relpath = svn_relpath_dirname(op_root_relpath, scratch_pool);


            SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, op_root_relpath));
            SVN_ERR(svn_sqlite__step(&have_row, stmt));

            if (! have_row)
              break;

            op_depth = svn_sqlite__column_int(stmt, 0);

            /* Skip to op_depth */
            tmp = op_root_relpath;

            op_root_relpath = svn_relpath_prefix(op_root_relpath, op_depth,
                                                 scratch_pool);
            repos_prefix_path = svn_relpath_join(
                                                 svn_relpath_skip_ancestor(op_root_relpath, tmp),
                                                 repos_prefix_path, scratch_pool);
          }

      SVN_ERR(svn_sqlite__reset(stmt));

      build_relpath = repos_prefix_path;

      /* If we're here, then we have an added/copied/moved (start) node, and
         CURRENT_ABSPATH now points to a BASE node. Figure out the repository
         information for the current node, and use that to compute the start
         node's repository information.  */
      SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, NULL,
                                                &base_relpath, repos_id,
                                                NULL, NULL, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL,
                                                wcroot, op_root_relpath,
                                                scratch_pool, scratch_pool));

        if (repos_relpath)
          *repos_relpath = svn_relpath_join(base_relpath, build_relpath,
                                            result_pool);
      }
    else
      SVN_ERR(svn_sqlite__reset(stmt));
  }
  /* Postconditions */
#ifdef SVN_DEBUG
  if (status)
    {
      SVN_ERR_ASSERT(*status == svn_wc__db_status_added
                     || *status == svn_wc__db_status_copied
                     || *status == svn_wc__db_status_incomplete
                     || *status == svn_wc__db_status_moved_here);
      if (*status == svn_wc__db_status_added)
        {
          SVN_ERR_ASSERT(!original_repos_relpath
                         || *original_repos_relpath == NULL);
          SVN_ERR_ASSERT(!original_revision
                         || *original_revision == SVN_INVALID_REVNUM);
          SVN_ERR_ASSERT(!original_repos_id
                         || *original_repos_id == INVALID_REPOS_ID);
        }
      /* An upgrade with a missing directory can leave INCOMPLETE working
         op-roots. See upgrade_tests.py 29: upgrade with missing replaced dir
       */
      else if (*status != svn_wc__db_status_incomplete)
        {
          SVN_ERR_ASSERT(!original_repos_relpath
                         || *original_repos_relpath != NULL);
          SVN_ERR_ASSERT(!original_revision
                         || *original_revision != SVN_INVALID_REVNUM);
          SVN_ERR_ASSERT(!original_repos_id
                         || *original_repos_id != INVALID_REPOS_ID);
        }
    }
  SVN_ERR_ASSERT(!op_root_relpath_p || *op_root_relpath_p != NULL);
#endif

  return SVN_NO_ERROR;
}