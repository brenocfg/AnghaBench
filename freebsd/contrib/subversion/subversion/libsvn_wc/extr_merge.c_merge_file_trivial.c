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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_dirent_is_child (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_files_contents_three_same_p (scalar_t__*,scalar_t__*,scalar_t__*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_get_wcroot (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_remove (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_wc_merge_merged ; 
 int svn_wc_merge_no_merge ; 
 int svn_wc_merge_unchanged ; 

__attribute__((used)) static svn_error_t *
merge_file_trivial(svn_skel_t **work_items,
                   enum svn_wc_merge_outcome_t *merge_outcome,
                   const char *left_abspath,
                   const char *right_abspath,
                   const char *target_abspath,
                   const char *detranslated_target_abspath,
                   svn_boolean_t dry_run,
                   svn_wc__db_t *db,
                   svn_cancel_func_t cancel_func,
                   void *cancel_baton,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_skel_t *work_item;
  svn_boolean_t same_left_right;
  svn_boolean_t same_right_target;
  svn_boolean_t same_left_target;
  svn_node_kind_t kind;
  svn_boolean_t is_special;

  /* If the target is not a normal file, do not attempt a trivial merge. */
  SVN_ERR(svn_io_check_special_path(target_abspath, &kind, &is_special,
                                    scratch_pool));
  if (kind != svn_node_file || is_special)
    {
      *merge_outcome = svn_wc_merge_no_merge;
      return SVN_NO_ERROR;
    }

  /* Check the files */
  SVN_ERR(svn_io_files_contents_three_same_p(&same_left_right,
                                             &same_right_target,
                                             &same_left_target,
                                             left_abspath,
                                             right_abspath,
                                             detranslated_target_abspath,
                                             scratch_pool));

  /* If the LEFT side of the merge is equal to WORKING, then we can
   * copy RIGHT directly. */
  if (same_left_target)
    {
      /* If the left side equals the right side, there is no change to merge
       * so we leave the target unchanged. */
      if (same_left_right)
        {
          *merge_outcome = svn_wc_merge_unchanged;
        }
      else
        {
          *merge_outcome = svn_wc_merge_merged;
          if (!dry_run)
            {
              const char *wcroot_abspath;
              svn_boolean_t delete_src = FALSE;

              /* The right_abspath might be outside our working copy. In that
                 case we should copy the file to a safe location before
                 installing to avoid breaking the workqueue.

                 This matches the behavior in preserve_pre_merge_files */

              SVN_ERR(svn_wc__db_get_wcroot(&wcroot_abspath,
                                            db, target_abspath,
                                            scratch_pool, scratch_pool));

              if (!svn_dirent_is_child(wcroot_abspath, right_abspath, NULL))
                {
                  svn_stream_t *tmp_src;
                  svn_stream_t *tmp_dst;
                  const char *tmp_dir;

                  SVN_ERR(svn_stream_open_readonly(&tmp_src, right_abspath,
                                                   scratch_pool,
                                                   scratch_pool));

                  SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tmp_dir, db,
                                                         target_abspath,
                                                         scratch_pool,
                                                         scratch_pool));

                  SVN_ERR(svn_stream_open_unique(&tmp_dst, &right_abspath,
                                                 tmp_dir, svn_io_file_del_none,
                                                 scratch_pool, scratch_pool));

                  SVN_ERR(svn_stream_copy3(tmp_src, tmp_dst,
                                           cancel_func, cancel_baton,
                                           scratch_pool));

                  delete_src = TRUE;
                }

              SVN_ERR(svn_wc__wq_build_file_install(
                        &work_item, db, target_abspath, right_abspath,
                        FALSE /* use_commit_times */,
                        FALSE /* record_fileinfo */,
                        result_pool, scratch_pool));
              *work_items = svn_wc__wq_merge(*work_items, work_item,
                                             result_pool);

              if (delete_src)
                {
                  SVN_ERR(svn_wc__wq_build_file_remove(
                                    &work_item, db, wcroot_abspath,
                                    right_abspath,
                                    result_pool, scratch_pool));
                  *work_items = svn_wc__wq_merge(*work_items, work_item,
                                                 result_pool);
                }
            }
        }

      return SVN_NO_ERROR;
    }
  else
    {
      /* If the locally existing, changed file equals the incoming 'right'
       * file, there is no conflict.  For binary files, we historically
       * conflicted them needlessly, while merge_text_file figured it out
       * eventually and returned svn_wc_merge_unchanged for them, which
       * is what we do here. */
      if (same_right_target)
        {
          *merge_outcome = svn_wc_merge_unchanged;
          return SVN_NO_ERROR;
        }
    }

  *merge_outcome = svn_wc_merge_no_merge;
  return SVN_NO_ERROR;
}