#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_11__ ;

/* Type definitions */
struct TYPE_34__ {int /*<<< orphan*/ * props; int /*<<< orphan*/  const* checksum; TYPE_1__* location_and_kind; } ;
typedef  TYPE_2__ working_node_version_t ;
struct TYPE_35__ {int /*<<< orphan*/  db; TYPE_11__* wcroot; int /*<<< orphan*/  operation; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; TYPE_1__* new_version; TYPE_1__* old_version; } ;
typedef  TYPE_3__ update_move_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_36__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_37__ {scalar_t__ skip; TYPE_3__* umb; } ;
typedef  TYPE_5__ node_move_baton_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_33__ {int /*<<< orphan*/  peg_rev; } ;
struct TYPE_32__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_4__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* copy_working_node (char const*,char const*,TYPE_11__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* create_conflict_markers (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* create_node_tree_conflict (int /*<<< orphan*/ **,TYPE_5__*,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* mark_node_edited (TYPE_5__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_11__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_pristine_get_path (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__internal_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_delete ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_missing ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_obstructed ; 
 int svn_wc_merge_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_state_unchanged ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 
 TYPE_4__* update_move_list_add (TYPE_11__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* update_working_props (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_3__*,char const*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tc_editor_update_incoming_moved_file(node_move_baton_t *nmb,
                                     const char *dst_relpath,
                                     const char *src_relpath,
                                     const svn_checksum_t *src_checksum,
                                     const svn_checksum_t *dst_checksum,
                                     apr_hash_t *dst_props,
                                     apr_hash_t *src_props,
                                     svn_boolean_t do_text_merge,
                                     apr_pool_t *scratch_pool)
{
  update_move_baton_t *b = nmb->umb;
  working_node_version_t old_version, new_version;
  const char *dst_abspath = svn_dirent_join(b->wcroot->abspath,
                                            dst_relpath,
                                            scratch_pool);
  svn_skel_t *conflict_skel = NULL;
  enum svn_wc_merge_outcome_t merge_outcome;
  svn_wc_notify_state_t prop_state = svn_wc_notify_state_unchanged;
  svn_wc_notify_state_t content_state = svn_wc_notify_state_unchanged;
  svn_skel_t *work_item, *work_items = NULL;
  svn_node_kind_t dst_kind_on_disk;
  const char *dst_repos_relpath;
  svn_boolean_t tree_conflict = FALSE;
  svn_node_kind_t dst_db_kind;
  svn_error_t *err;

  SVN_ERR(mark_node_edited(nmb, scratch_pool));
  if (nmb->skip)
    return SVN_NO_ERROR;

  err = svn_wc__db_base_get_info_internal(NULL, &dst_db_kind, NULL,
                                          &dst_repos_relpath,
                                          NULL, NULL, NULL, NULL, NULL, NULL,
                                          NULL, NULL, NULL, NULL, NULL,
                                          b->wcroot, dst_relpath,
                                          scratch_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
    {
      const char *dst_parent_relpath;
      const char *dst_parent_repos_relpath;
      const char *src_abspath;

      /* If the file cannot be found, it was either deleted at the
       * move destination, or it was moved after its parent was moved.
       * We cannot deal with this problem right now. Instead, we will
       * raise a new tree conflict at the location where this file should
       * have been, and let another run of the resolver deal with the
       * new conflict later on. */

      svn_error_clear(err);

      /* Create a WORKING node for this file at the move destination. */
      SVN_ERR(copy_working_node(src_relpath, dst_relpath, b->wcroot,
                                scratch_pool));

      /* Raise a tree conflict at the new WORKING node. */
      dst_db_kind = svn_node_none;
      SVN_ERR(create_node_tree_conflict(&conflict_skel, nmb, dst_relpath,
                                        svn_node_file, dst_db_kind,
                                        svn_wc_conflict_reason_edited,
                                        svn_wc_conflict_action_delete,
                                        NULL, scratch_pool, scratch_pool));
      dst_parent_relpath = svn_relpath_dirname(dst_relpath, scratch_pool);
      SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, NULL,
                                                &dst_parent_repos_relpath,
                                                NULL, NULL, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL,
                                                NULL, b->wcroot,
                                                dst_parent_relpath,
                                                scratch_pool, scratch_pool));
      dst_repos_relpath = svn_relpath_join(dst_parent_repos_relpath,
                                           svn_relpath_basename(dst_relpath,
                                                                scratch_pool),
                                           scratch_pool);
      tree_conflict = TRUE;

      /* Schedule a copy of the victim's file content to the new node's path. */
      src_abspath = svn_dirent_join(b->wcroot->abspath, src_relpath,
                                    scratch_pool);
      SVN_ERR(svn_wc__wq_build_file_install(&work_item, b->db,
                                            dst_abspath,
                                            src_abspath,
                                            FALSE /*FIXME: use_commit_times?*/,
                                            TRUE  /* record_file_info */,
                                            scratch_pool, scratch_pool));
      work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);
    }
  else
    SVN_ERR(err);

  if ((dst_db_kind == svn_node_none || dst_db_kind != svn_node_file) &&
      conflict_skel == NULL)
    {
      SVN_ERR(create_node_tree_conflict(&conflict_skel, nmb, dst_relpath,
                                        svn_node_file, dst_db_kind,
                                        dst_db_kind == svn_node_none
                                          ? svn_wc_conflict_reason_missing
                                          : svn_wc_conflict_reason_obstructed,
                                        svn_wc_conflict_action_edit,
                                        NULL,
                                        scratch_pool, scratch_pool));
      tree_conflict = TRUE;
    }

  SVN_ERR(svn_io_check_path(dst_abspath, &dst_kind_on_disk, scratch_pool));
  if ((dst_kind_on_disk == svn_node_none || dst_kind_on_disk != svn_node_file)
      && conflict_skel == NULL)
    {
      SVN_ERR(create_node_tree_conflict(&conflict_skel, nmb, dst_relpath,
                                        svn_node_file, dst_kind_on_disk,
                                        dst_kind_on_disk == svn_node_none
                                          ? svn_wc_conflict_reason_missing
                                          : svn_wc_conflict_reason_obstructed,
                                        svn_wc_conflict_action_edit,
                                        NULL,
                                        scratch_pool, scratch_pool));
      tree_conflict = TRUE;
    }

  old_version.location_and_kind = b->old_version;
  new_version.location_and_kind = b->new_version;

  old_version.checksum = src_checksum;
  old_version.props = src_props;
  new_version.checksum = dst_checksum;
  new_version.props = dst_props;

  /* Merge properties and text content if there is no tree conflict. */
  if (conflict_skel == NULL)
    {
      apr_hash_t *actual_props;
      apr_array_header_t *propchanges;

      SVN_ERR(update_working_props(&prop_state, &conflict_skel, &propchanges,
                                   &actual_props, b, dst_relpath,
                                   &old_version, &new_version,
                                   scratch_pool, scratch_pool));
      if (do_text_merge)
        {
          const char *old_pristine_abspath;
          const char *src_abspath;
          const char *label_left;
          const char *label_target;

          /*
           * Run a 3-way merge to update the file at its post-move location,
           * using the pre-move file's pristine text as the merge base, the
           * post-move content as the merge-right version, and the current
           * content of the working file at the pre-move location as the
           * merge-left version.
           */
          SVN_ERR(svn_wc__db_pristine_get_path(&old_pristine_abspath,
                                               b->db, b->wcroot->abspath,
                                               src_checksum,
                                               scratch_pool, scratch_pool));
          src_abspath = svn_dirent_join(b->wcroot->abspath, src_relpath,
                                        scratch_pool);
          label_left = apr_psprintf(scratch_pool, ".r%ld",
                                    b->old_version->peg_rev);
          label_target = apr_psprintf(scratch_pool, ".r%ld",
                                      b->new_version->peg_rev);
          SVN_ERR(svn_wc__internal_merge(&work_item, &conflict_skel,
                                         &merge_outcome, b->db,
                                         old_pristine_abspath,
                                         src_abspath,
                                         dst_abspath,
                                         dst_abspath,
                                         label_left,
                                         _(".working"),
                                         label_target,
                                         actual_props,
                                         FALSE, /* dry-run */
                                         NULL, /* diff3-cmd */
                                         NULL, /* merge options */
                                         propchanges,
                                         b->cancel_func, b->cancel_baton,
                                         scratch_pool, scratch_pool));

          work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);

          if (merge_outcome == svn_wc_merge_conflict)
            content_state = svn_wc_notify_state_conflicted;
          else
            content_state = svn_wc_notify_state_merged;
        }
    }

  /* If there are any conflicts to be stored, convert them into work items
   * too. */
  if (conflict_skel)
    {
      SVN_ERR(create_conflict_markers(&work_item, dst_abspath, b->db,
                                      dst_repos_relpath, conflict_skel,
                                      b->operation, &old_version, &new_version,
                                      svn_node_file, !tree_conflict,
                                      scratch_pool, scratch_pool));

      work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);
    }

  SVN_ERR(update_move_list_add(b->wcroot, dst_relpath, b->db,
                               svn_wc_notify_update_update,
                               svn_node_file,
                               content_state,
                               prop_state,
                               conflict_skel, work_items, scratch_pool));

  return SVN_NO_ERROR;
}