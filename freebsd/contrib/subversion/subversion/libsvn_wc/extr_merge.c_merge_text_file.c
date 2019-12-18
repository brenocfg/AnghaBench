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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_4__ {char const* local_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  old_actual_props; int /*<<< orphan*/  merge_options; int /*<<< orphan*/  diff3_cmd; int /*<<< orphan*/  wri_abspath; } ;
typedef  TYPE_1__ merge_target_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  do_text_merge (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_text_merge_external (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preserve_pre_merge_files (int /*<<< orphan*/ **,char const**,char const**,char const**,TYPE_1__ const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_files_contents_same_p (scalar_t__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_uniquely_named (int /*<<< orphan*/ **,char const**,char const*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_text_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_translate_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_remove (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_wc_merge_conflict ; 
 int svn_wc_merge_merged ; 
 int svn_wc_merge_unchanged ; 

__attribute__((used)) static svn_error_t*
merge_text_file(svn_skel_t **work_items,
                svn_skel_t **conflict_skel,
                enum svn_wc_merge_outcome_t *merge_outcome,
                const merge_target_t *mt,
                const char *left_abspath,
                const char *right_abspath,
                const char *left_label,
                const char *right_label,
                const char *target_label,
                svn_boolean_t dry_run,
                const char *detranslated_target_abspath,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  apr_pool_t *pool = scratch_pool;  /* ### temporary rename  */
  svn_boolean_t contains_conflicts;
  apr_file_t *result_f;
  const char *result_target;
  const char *base_name;
  const char *temp_dir;
  svn_skel_t *work_item;

  *work_items = NULL;

  base_name = svn_dirent_basename(mt->local_abspath, scratch_pool);

  /* Open a second temporary file for writing; this is where diff3
     will write the merged results.  We want to use a tempfile
     with a name that reflects the original, in case this
     ultimately winds up in a conflict resolution editor.  */
  SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&temp_dir, mt->db, mt->wri_abspath,
                                         pool, pool));
  SVN_ERR(svn_io_open_uniquely_named(&result_f, &result_target,
                                     temp_dir, base_name, ".tmp",
                                     svn_io_file_del_none, pool, pool));

  /* Run the external or internal merge, as requested. */
  if (mt->diff3_cmd)
      SVN_ERR(do_text_merge_external(&contains_conflicts,
                                     result_f,
                                     mt->diff3_cmd,
                                     mt->merge_options,
                                     detranslated_target_abspath,
                                     left_abspath,
                                     right_abspath,
                                     target_label,
                                     left_label,
                                     right_label,
                                     pool));
  else /* Use internal merge. */
    SVN_ERR(do_text_merge(&contains_conflicts,
                          result_f,
                          mt->merge_options,
                          detranslated_target_abspath,
                          left_abspath,
                          right_abspath,
                          target_label,
                          left_label,
                          right_label,
                          cancel_func, cancel_baton,
                          pool));

  SVN_ERR(svn_io_file_close(result_f, pool));

  /* Determine the MERGE_OUTCOME, and record any conflict. */
  if (contains_conflicts)
    {
      *merge_outcome = svn_wc_merge_conflict;

      if (! dry_run)
        {
          const char *left_copy, *right_copy, *target_copy;

          /* Preserve the three conflict files */
          SVN_ERR(preserve_pre_merge_files(
                    &work_item,
                    &left_copy, &right_copy, &target_copy,
                    mt, left_abspath, right_abspath,
                    left_label, right_label, target_label,
                    detranslated_target_abspath,
                    cancel_func, cancel_baton,
                    result_pool, scratch_pool));
          *work_items = svn_wc__wq_merge(*work_items, work_item, result_pool);

          /* Track the conflict marker files in the metadata. */

          if (!*conflict_skel)
            *conflict_skel = svn_wc__conflict_skel_create(result_pool);

          SVN_ERR(svn_wc__conflict_skel_add_text_conflict(*conflict_skel,
                                                          mt->db, mt->local_abspath,
                                                          target_copy,
                                                          left_copy,
                                                          right_copy,
                                                          result_pool,
                                                          scratch_pool));
        }
    }
  else
    {
      svn_boolean_t same, special;

      /* If 'special', then use the detranslated form of the
         target file.  This is so we don't try to follow symlinks,
         but the same treatment is probably also appropriate for
         whatever special file types we may invent in the future. */
      SVN_ERR(svn_wc__get_translate_info(NULL, NULL, NULL,
                                         &special, mt->db, mt->local_abspath,
                                         mt->old_actual_props, TRUE,
                                         pool, pool));
      SVN_ERR(svn_io_files_contents_same_p(&same, result_target,
                                           (special ?
                                              detranslated_target_abspath :
                                              mt->local_abspath),
                                           pool));

      *merge_outcome = same ? svn_wc_merge_unchanged : svn_wc_merge_merged;
    }

  if (*merge_outcome != svn_wc_merge_unchanged && ! dry_run)
    {
      /* replace TARGET_ABSPATH with the new merged file, expanding. */
      SVN_ERR(svn_wc__wq_build_file_install(&work_item,
                                            mt->db, mt->local_abspath,
                                            result_target,
                                            FALSE /* use_commit_times */,
                                            FALSE /* record_fileinfo */,
                                            result_pool, scratch_pool));
      *work_items = svn_wc__wq_merge(*work_items, work_item, result_pool);
    }

  /* Remove the tempfile after use */
  SVN_ERR(svn_wc__wq_build_file_remove(&work_item, mt->db, mt->local_abspath,
                                       result_target,
                                       result_pool, scratch_pool));

  *work_items = svn_wc__wq_merge(*work_items, work_item, result_pool);

  return SVN_NO_ERROR;
}