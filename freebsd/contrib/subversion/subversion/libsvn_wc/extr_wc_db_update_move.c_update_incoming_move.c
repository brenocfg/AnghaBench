#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* cancel_baton; int /*<<< orphan*/  cancel_func; TYPE_3__* wcroot; int /*<<< orphan*/ * db; TYPE_2__* new_version; TYPE_2__* old_version; int /*<<< orphan*/  operation; void* src_op_depth; void* dst_op_depth; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ update_move_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
struct TYPE_14__ {int /*<<< orphan*/  peg_rev; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_url; int /*<<< orphan*/  path_in_repos; int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_2__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
struct TYPE_15__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_3__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_16__ {char const* src_relpath; char const* dst_relpath; TYPE_1__* umb; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ node_move_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CREATE_UPDATE_MOVE_LIST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* relpath_depth (char const*) ; 
 int /*<<< orphan*/  suitable_for_move (TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_depth_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_has_local_mods (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_incoming_moved_node (TYPE_4__*,TYPE_3__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_write_lock (TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_incoming_move(svn_revnum_t *old_rev,
                    svn_revnum_t *new_rev,
                    svn_wc__db_t *db,
                    svn_wc__db_wcroot_t *wcroot,
                    const char *local_relpath,
                    const char *dst_relpath,
                    svn_wc_operation_t operation,
                    svn_wc_conflict_action_t action,
                    svn_wc_conflict_reason_t reason,
                    svn_cancel_func_t cancel_func,
                    void *cancel_baton,
                    apr_pool_t *scratch_pool)
{
  update_move_baton_t umb = { NULL };
  svn_wc_conflict_version_t old_version;
  svn_wc_conflict_version_t new_version;
  apr_int64_t repos_id;
  node_move_baton_t nmb = { 0 };
  svn_boolean_t is_modified;

  SVN_ERR_ASSERT(svn_relpath_skip_ancestor(dst_relpath, local_relpath) == NULL);

  /* For incoming moves during update/switch, the move source is a copied
   * tree which was copied from the pre-update BASE revision while raising
   * the tree conflict, when the update attempted to delete the move source.
   * This copy is our "original" state (SRC of the diff) and the local changes
   * on top of this copy at the top-most WORKING layer are used to drive the
   * editor (DST of the diff).
   *
   * The move destination, where changes are applied to, is now in the BASE
   * tree at DST_RELPATH. This repository-side move is the "incoming change"
   * recorded for any tree conflicts created during the editor drive.
   * We assume this path contains no local changes, and create local changes
   * in DST_RELPATH corresponding to changes contained in the conflict victim.
   * 
   * DST_OP_DEPTH is used to infer the "op-root" of the incoming move. This
   * "op-root" is virtual because all nodes belonging to the incoming move
   * live in the BASE tree. It is used for constructing repository paths
   * when new tree conflicts need to be raised.
   */
  umb.src_op_depth = relpath_depth(local_relpath); /* SRC of diff */
  umb.dst_op_depth = relpath_depth(dst_relpath); /* virtual DST op-root */

  SVN_ERR(verify_write_lock(wcroot, local_relpath, scratch_pool));
  SVN_ERR(verify_write_lock(wcroot, dst_relpath, scratch_pool));

  /* Make sure there are no local modifications in the move destination. */
  SVN_ERR(svn_wc__node_has_local_mods(&is_modified, NULL, db,
                                      svn_dirent_join(wcroot->abspath,
                                                      dst_relpath,
                                                      scratch_pool),
                                      TRUE, cancel_func, cancel_baton,
                                      scratch_pool));
  if (is_modified)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Cannot merge local changes from '%s' because "
                               "'%s' already contains other local changes "
                               "(please commit or revert these other changes "
                               "and try again)"),
                             svn_dirent_local_style(
                               svn_dirent_join(wcroot->abspath, local_relpath,
                                               scratch_pool),
                               scratch_pool),
                             svn_dirent_local_style(
                               svn_dirent_join(wcroot->abspath, dst_relpath,
                                               scratch_pool),
                               scratch_pool));

  /* Check for switched subtrees and mixed-revision working copy. */
  SVN_ERR(suitable_for_move(wcroot, dst_relpath, scratch_pool));

  /* Read version info from the updated incoming post-move location. */
  SVN_ERR(svn_wc__db_base_get_info_internal(NULL, &new_version.node_kind,
                                            &new_version.peg_rev,
                                            &new_version.path_in_repos,
                                            &repos_id,
                                            NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL,
                                            wcroot, dst_relpath,
                                            scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_fetch_repos_info(&new_version.repos_url,
                                      &new_version.repos_uuid,
                                      wcroot, repos_id,
                                      scratch_pool));

  /* Read version info from the victim's location. */
  SVN_ERR(svn_wc__db_depth_get_info(NULL, &old_version.node_kind,
                                    &old_version.peg_rev,
                                    &old_version.path_in_repos, &repos_id,
                                    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                    NULL, wcroot,
                                    local_relpath, umb.src_op_depth,
                                    scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_fetch_repos_info(&old_version.repos_url,
                                      &old_version.repos_uuid,
                                      wcroot, repos_id,
                                      scratch_pool));
  *old_rev = old_version.peg_rev;
  *new_rev = new_version.peg_rev;

  umb.operation = operation;
  umb.old_version= &old_version;
  umb.new_version= &new_version;
  umb.db = db;
  umb.wcroot = wcroot;
  umb.cancel_func = cancel_func;
  umb.cancel_baton = cancel_baton;

  /* Create a new, and empty, list for notification information. */
  SVN_ERR(svn_sqlite__exec_statements(wcroot->sdb,
                                      STMT_CREATE_UPDATE_MOVE_LIST));

  /* Drive the editor... */

  nmb.umb = &umb;
  nmb.src_relpath = local_relpath;
  nmb.dst_relpath = dst_relpath;
  /* nmb.shadowed = FALSE; */
  /* nmb.edited = FALSE; */
  /* nmb.skip_children = FALSE; */

  /* We walk the conflict victim, comparing each node with the equivalent node
   * at the WORKING layer, applying any local changes to nodes at the move
   * destination. */
  SVN_ERR(update_incoming_moved_node(&nmb, wcroot, local_relpath, dst_relpath,
                                     scratch_pool));

  return SVN_NO_ERROR;
}