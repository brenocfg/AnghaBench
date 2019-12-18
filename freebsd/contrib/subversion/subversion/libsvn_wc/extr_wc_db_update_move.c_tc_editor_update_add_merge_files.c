#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  db; TYPE_4__* wcroot; int /*<<< orphan*/  new_version; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ update_local_add_baton_t ;
typedef  scalar_t__ svn_wc_notify_state_t ;
struct TYPE_13__ {char const* path_in_repos; int /*<<< orphan*/  peg_rev; scalar_t__ node_kind; } ;
typedef  TYPE_2__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_14__ {int /*<<< orphan*/  local_relpath; TYPE_1__* b; scalar_t__ skip; } ;
typedef  TYPE_3__ added_node_baton_t ;
struct TYPE_15__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_create_markers (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_path (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_conflict_version_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svn_wc_merge_conflict ; 
 scalar_t__ svn_wc_notify_state_changed ; 
 scalar_t__ svn_wc_notify_state_conflicted ; 
 scalar_t__ svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 
 int /*<<< orphan*/  update_incoming_add_merge_props (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_local_add_mark_node_edited (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_local_add_notify_obstructed_or_missing (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_move_list_add (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tc_editor_update_add_merge_files(added_node_baton_t *nb,
                                 const svn_checksum_t *working_checksum,
                                 const svn_checksum_t *base_checksum,
                                 apr_hash_t *working_props,
                                 apr_hash_t *base_props,
                                 apr_pool_t *scratch_pool)
{
  update_local_add_baton_t *b = nb->b;
  apr_array_header_t *propchanges;
  svn_boolean_t is_modified;
  enum svn_wc_merge_outcome_t merge_outcome;
  svn_skel_t *conflict_skel = NULL;
  svn_wc_notify_state_t prop_state, content_state;
  svn_skel_t *work_items = NULL;
  svn_node_kind_t kind_on_disk;
  const char *local_abspath = svn_dirent_join(b->wcroot->abspath,
                                              nb->local_relpath,
                                              scratch_pool);

  SVN_ERR(update_local_add_mark_node_edited(nb, scratch_pool));
  if (nb->skip)
    return SVN_NO_ERROR;

  /* Check for on-disk obstructions or missing files. */
  SVN_ERR(svn_io_check_path(local_abspath, &kind_on_disk, scratch_pool));
  if (kind_on_disk != svn_node_file)
    {
      SVN_ERR(update_local_add_notify_obstructed_or_missing(nb, svn_node_file,
                                                            kind_on_disk,
                                                            scratch_pool));
      nb->skip = TRUE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(update_incoming_add_merge_props(&prop_state, &conflict_skel,
                                          nb->local_relpath,
                                          base_props, working_props,
                                          b->db, b->wcroot,
                                          scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__internal_file_modified_p(&is_modified,
                                           b->db, local_abspath,
                                           FALSE /* exact_comparison */,
                                           scratch_pool));
  if (!is_modified)
    {
      svn_skel_t *work_item = NULL;

      SVN_ERR(svn_wc__wq_build_file_install(&work_item, b->db,
                                            local_abspath, NULL,
                                            /* FIXME: use_commit_times? */
                                            FALSE,
                                            TRUE,  /* record_file_info */
                                            scratch_pool, scratch_pool));
      work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);
      content_state = svn_wc_notify_state_changed;
    }
  else
    {
      const char *empty_file_abspath;
      const char *pristine_abspath;
      svn_skel_t *work_item = NULL;

      /*
       * Run a 3-way merge to update the file, using the empty file
       * merge base, the post-update pristine text as the merge-left version,
       * and the locally added content of the working file as the merge-right
       * version.
       */
      SVN_ERR(svn_io_open_unique_file3(NULL, &empty_file_abspath, NULL,
                                       svn_io_file_del_on_pool_cleanup,
                                       scratch_pool, scratch_pool));
      SVN_ERR(svn_wc__db_pristine_get_path(&pristine_abspath, b->db,
                                           b->wcroot->abspath, base_checksum,
                                           scratch_pool, scratch_pool));

      /* Create a property diff which shows all props as added. */
      SVN_ERR(svn_prop_diffs(&propchanges, working_props,
                             apr_hash_make(scratch_pool), scratch_pool));

      SVN_ERR(svn_wc__internal_merge(&work_item, &conflict_skel,
                                     &merge_outcome, b->db,
                                     empty_file_abspath,
                                     pristine_abspath,
                                     local_abspath,
                                     local_abspath,
                                     NULL, NULL, NULL, /* diff labels */
                                     apr_hash_make(scratch_pool),
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

  /* If there are any conflicts to be stored, convert them into work items
   * too. */
  if (conflict_skel)
    {
      svn_wc_conflict_version_t *new_version;
      svn_node_kind_t new_kind;
      svn_revnum_t new_rev;
      const char *repos_relpath;

      new_version = svn_wc_conflict_version_dup(nb->b->new_version,
                                                scratch_pool);
      SVN_ERR(svn_wc__db_base_get_info_internal(NULL, &new_kind, &new_rev,
                                                &repos_relpath, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL,
                                                b->wcroot, nb->local_relpath,
                                                scratch_pool, scratch_pool));
      /* Fill in conflict info templates with info for this node. */
      new_version->path_in_repos = repos_relpath;
      new_version->node_kind = new_kind;
      new_version->peg_rev = new_rev;

      /* Create conflict markers. */
      SVN_ERR(svn_wc__conflict_skel_set_op_update(conflict_skel, NULL,
                                                  new_version, scratch_pool,
                                                  scratch_pool));
      if (prop_state == svn_wc_notify_state_conflicted)
        SVN_ERR(svn_wc__conflict_create_markers(&work_items, b->db,
                                                local_abspath,
                                                conflict_skel,
                                                scratch_pool,
                                                scratch_pool));
    }

  SVN_ERR(update_move_list_add(b->wcroot, nb->local_relpath, b->db,
                               svn_wc_notify_update_update,
                               svn_node_file, content_state, prop_state,
                               conflict_skel, work_items, scratch_pool));

  return SVN_NO_ERROR;
}