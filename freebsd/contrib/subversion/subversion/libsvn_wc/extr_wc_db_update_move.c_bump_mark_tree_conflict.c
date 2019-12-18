#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  create_tree_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_wc__db_depth_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_moved_away ; 
 int /*<<< orphan*/ * svn_wc_conflict_version_create2 (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 
 int /*<<< orphan*/  update_move_list_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_write_lock (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bump_mark_tree_conflict(svn_wc__db_wcroot_t *wcroot,
                        const char *move_src_root_relpath,
                        int src_op_depth,
                        const char *move_src_op_root_relpath,
                        const char *move_dst_op_root_relpath,
                        svn_wc__db_t *db,
                        apr_pool_t *scratch_pool)
{
  apr_int64_t repos_id;
  const char *repos_root_url;
  const char *repos_uuid;
  const char *old_repos_relpath;
  const char *new_repos_relpath;
  svn_revnum_t old_rev;
  svn_revnum_t new_rev;
  svn_node_kind_t old_kind;
  svn_node_kind_t new_kind;
  svn_wc_conflict_version_t *old_version;
  svn_wc_conflict_version_t *new_version;
  svn_skel_t *conflict;

  /* Verify precondition: We are allowed to set a tree conflict here. */
  SVN_ERR(verify_write_lock(wcroot, move_src_root_relpath, scratch_pool));

  /* Read new (post-update) information from the new move source BASE node. */
  SVN_ERR(svn_wc__db_depth_get_info(NULL, &new_kind, &new_rev,
                                    &new_repos_relpath, &repos_id,
                                    NULL, NULL, NULL, NULL, NULL,
                                    NULL, NULL, NULL,
                                    wcroot, move_src_op_root_relpath,
                                    src_op_depth, scratch_pool, scratch_pool));
  SVN_ERR(svn_wc__db_fetch_repos_info(&repos_root_url, &repos_uuid,
                                      wcroot, repos_id, scratch_pool));

  /* Read old (pre-update) information from the move destination node.

     This potentially touches nodes that aren't locked by us, but that is not
     a problem because we have a SQLite write lock here, and all sqlite
     operations that affect move stability use a sqlite lock as well.
     (And affecting the move itself requires a write lock on the node that
      we do own the lock for: the move source)
  */
  SVN_ERR(svn_wc__db_depth_get_info(NULL, &old_kind, &old_rev,
                                    &old_repos_relpath, NULL, NULL, NULL,
                                    NULL, NULL, NULL, NULL, NULL, NULL,
                                    wcroot, move_dst_op_root_relpath,
                                    relpath_depth(move_dst_op_root_relpath),
                                    scratch_pool, scratch_pool));

  if (strcmp(move_src_root_relpath, move_src_op_root_relpath))
    {
      /* We have information for the op-root, but need it for the node that
         we are putting the tree conflict on. Luckily we know that we have
         a clean BASE */

      const char *rpath = svn_relpath_skip_ancestor(move_src_op_root_relpath,
                                                    move_src_root_relpath);

      old_repos_relpath = svn_relpath_join(old_repos_relpath, rpath,
                                           scratch_pool);
      new_repos_relpath = svn_relpath_join(new_repos_relpath, rpath,
                                           scratch_pool);
    }

  old_version = svn_wc_conflict_version_create2(
                  repos_root_url, repos_uuid, old_repos_relpath, old_rev,
                  old_kind, scratch_pool);
  new_version = svn_wc_conflict_version_create2(
                  repos_root_url, repos_uuid, new_repos_relpath, new_rev,
                  new_kind, scratch_pool);

  SVN_ERR(create_tree_conflict(&conflict, wcroot, move_src_root_relpath,
                               move_dst_op_root_relpath,
                               db, old_version, new_version,
                               svn_wc_operation_update,
                               old_kind, new_kind,
                               old_repos_relpath,
                               svn_wc_conflict_reason_moved_away,
                               svn_wc_conflict_action_edit,
                               move_src_op_root_relpath,
                               scratch_pool, scratch_pool));

  SVN_ERR(update_move_list_add(wcroot, move_src_root_relpath, db,
                               svn_wc_notify_tree_conflict,
                               new_kind,
                               svn_wc_notify_state_inapplicable,
                               svn_wc_notify_state_inapplicable,
                               conflict, NULL, scratch_pool));

  return SVN_NO_ERROR;
}