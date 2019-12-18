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
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int svn_boolean_t ;
struct svn_wc__db_base_info_t {scalar_t__ kind; scalar_t__ status; scalar_t__ revnum; char* repos_relpath; scalar_t__ update_root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_BASE_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 struct svn_wc__db_base_info_t* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base_get_children_info (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * db_op_set_rev_repos_relpath_iprops (TYPE_1__*,char const*,int /*<<< orphan*/ *,scalar_t__,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 char const* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

__attribute__((used)) static svn_error_t *
bump_node_revision(svn_wc__db_wcroot_t *wcroot,
                   const char *local_relpath,
                   svn_wc__db_status_t node_status,
                   svn_node_kind_t node_kind,
                   svn_revnum_t node_revision,
                   const char *node_repos_relpath,
                   apr_int64_t new_repos_id,
                   const char *new_repos_relpath,
                   svn_revnum_t new_rev,
                   svn_depth_t depth,
                   apr_hash_t *exclude_relpaths,
                   apr_hash_t *wcroot_iprops,
                   svn_boolean_t is_root,
                   svn_boolean_t skip_when_dir,
                   svn_wc__db_t *db,
                   apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  apr_hash_t *children;
  apr_hash_index_t *hi;
  svn_boolean_t set_repos_relpath = FALSE;
  svn_depth_t depth_below_here = depth;
  apr_array_header_t *iprops = NULL;

  if (new_repos_relpath != NULL
      && strcmp(node_repos_relpath, new_repos_relpath))
    set_repos_relpath = TRUE;

  if (wcroot_iprops)
    iprops = svn_hash_gets(wcroot_iprops,
                           svn_dirent_join(wcroot->abspath, local_relpath,
                                           scratch_pool));

  if (iprops
      || set_repos_relpath
      || (SVN_IS_VALID_REVNUM(new_rev) && new_rev != node_revision))
    {
      SVN_ERR(db_op_set_rev_repos_relpath_iprops(wcroot, local_relpath,
                                                 iprops, new_rev,
                                                 set_repos_relpath,
                                                 new_repos_relpath,
                                                 new_repos_id,
                                                 scratch_pool));
    }

  /* Early out */
  if (depth <= svn_depth_empty
      || node_kind != svn_node_dir
      || node_status == svn_wc__db_status_server_excluded
      || node_status == svn_wc__db_status_excluded
      || node_status == svn_wc__db_status_not_present)
    return SVN_NO_ERROR;

  /* And now recurse over the children */

  depth_below_here = depth;

  if (depth == svn_depth_immediates || depth == svn_depth_files)
    depth_below_here = svn_depth_empty;

  iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(base_get_children_info(&children, wcroot, local_relpath, 0,
                                 scratch_pool, iterpool));
  for (hi = apr_hash_first(scratch_pool, children); hi; hi = apr_hash_next(hi))
    {
      const char *child_basename = apr_hash_this_key(hi);
      const struct svn_wc__db_base_info_t *child_info;
      const char *child_local_relpath;
      const char *child_repos_relpath = NULL;

      svn_pool_clear(iterpool);

      child_info = apr_hash_this_val(hi);

      if (child_info->update_root && child_info->kind == svn_node_file)
        continue; /* Skip file externals */

      if (depth < svn_depth_immediates && child_info->kind == svn_node_dir)
          continue; /* Skip directories */

      child_local_relpath = svn_relpath_join(local_relpath, child_basename,
                                             iterpool);

      /* Don't touch nodes that can't be touched via the exclude list */
      if (svn_hash_gets(exclude_relpaths, child_local_relpath))
          continue;

      /* If the node is still marked 'not-present', then the server did not
          re-add it.  So it's really gone in this revision, thus we remove the
          node.

          If the node is still marked 'server-excluded' and yet is not the same
          revision as new_rev, then the server did not re-add it, nor
          re-server-exclude it, so we can remove the node. */
      if (child_info->status == svn_wc__db_status_not_present
          || (child_info->status == svn_wc__db_status_server_excluded &&
              child_info->revnum != new_rev))
        {
          svn_sqlite__stmt_t *stmt;
          SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_BASE_NODE));
          SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, child_local_relpath));
          SVN_ERR(svn_sqlite__step_done(stmt));
          continue;
        }

      /* Derive the new URL for the current (child) entry */
      if (new_repos_relpath)
        child_repos_relpath = svn_relpath_join(new_repos_relpath,
                                               child_basename, iterpool);

      SVN_ERR(bump_node_revision(wcroot, child_local_relpath,
                                 child_info->status,
                                 child_info->kind,
                                 child_info->revnum,
                                 child_info->repos_relpath,
                                 new_repos_id,
                                 child_repos_relpath, new_rev,
                                 depth_below_here,
                                 exclude_relpaths, wcroot_iprops,
                                 FALSE /* is_root */,
                                 (depth < svn_depth_immediates), db,
                                 iterpool));
    }

  /* Cleanup */
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}