#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ merge_target_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_file (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_open_uniquely_named (int /*<<< orphan*/ *,char const**,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_text_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_move (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_wc_merge_conflict ; 

__attribute__((used)) static svn_error_t *
merge_binary_file(svn_skel_t **work_items,
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
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  apr_pool_t *pool = scratch_pool;  /* ### temporary rename  */
  /* ### when making the binary-file backups, should we be honoring
     keywords and eol stuff?   */
  const char *left_copy, *right_copy;
  const char *merge_dirpath, *merge_filename;
  const char *conflict_wrk;

  *work_items = NULL;

  svn_dirent_split(&merge_dirpath, &merge_filename, mt->local_abspath, pool);

  if (dry_run)
    {
      *merge_outcome = svn_wc_merge_conflict;
      return SVN_NO_ERROR;
    }

  /* reserve names for backups of left and right fulltexts */
  SVN_ERR(svn_io_open_uniquely_named(NULL,
                                     &left_copy,
                                     merge_dirpath,
                                     merge_filename,
                                     left_label,
                                     svn_io_file_del_none,
                                     pool, pool));

  SVN_ERR(svn_io_open_uniquely_named(NULL,
                                     &right_copy,
                                     merge_dirpath,
                                     merge_filename,
                                     right_label,
                                     svn_io_file_del_none,
                                     pool, pool));

  /* create the backup files */
  SVN_ERR(svn_io_copy_file(left_abspath, left_copy, TRUE, pool));
  SVN_ERR(svn_io_copy_file(right_abspath, right_copy, TRUE, pool));

  /* Was the merge target detranslated? */
  if (strcmp(mt->local_abspath, detranslated_target_abspath) != 0)
    {
      /* Create a .mine file too */
      SVN_ERR(svn_io_open_uniquely_named(NULL,
                                         &conflict_wrk,
                                         merge_dirpath,
                                         merge_filename,
                                         target_label,
                                         svn_io_file_del_none,
                                         pool, pool));
      SVN_ERR(svn_wc__wq_build_file_move(work_items, mt->db,
                                         mt->local_abspath,
                                         detranslated_target_abspath,
                                         conflict_wrk,
                                         pool, result_pool));
    }
  else
    {
      conflict_wrk = NULL;
    }

  /* Mark target_abspath's entry as "Conflicted", and start tracking
     the backup files in the entry as well. */
  if (!*conflict_skel)
    *conflict_skel = svn_wc__conflict_skel_create(result_pool);

  SVN_ERR(svn_wc__conflict_skel_add_text_conflict(*conflict_skel,
                                                  mt->db, mt->local_abspath,
                                                  conflict_wrk,
                                                  left_copy,
                                                  right_copy,
                                                  result_pool, scratch_pool));

  *merge_outcome = svn_wc_merge_conflict; /* a conflict happened */

  return SVN_NO_ERROR;
}