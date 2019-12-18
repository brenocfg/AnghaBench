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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM_EMPTY_FILE ; 
 int /*<<< orphan*/  ADM_README ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PROPS_SUBDIR ; 
 int /*<<< orphan*/  PROP_BASE_FOR_DIR ; 
 int /*<<< orphan*/  PROP_BASE_SUBDIR ; 
 int /*<<< orphan*/  PROP_REVERT_FOR_DIR ; 
 int /*<<< orphan*/  PROP_WORKING_FOR_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_WC__ADM_ENTRIES ; 
 int /*<<< orphan*/  SVN_WC__ADM_FORMAT ; 
 int /*<<< orphan*/  TEXT_BASE_SUBDIR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WCPROPS_ALL_DATA ; 
 int /*<<< orphan*/  WCPROPS_FNAME_FOR_DIR ; 
 int /*<<< orphan*/  WCPROPS_SUBDIR_FOR_FILES ; 
 int /*<<< orphan*/  build_lockfile_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  iterpool ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_cleanup_tmp_area (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wipe_obsolete_files(const char *wcroot_abspath, apr_pool_t *scratch_pool)
{
  /* Zap unused files.  */
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      SVN_WC__ADM_FORMAT,
                                      scratch_pool),
                    TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      SVN_WC__ADM_ENTRIES,
                                      scratch_pool),
                    TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      ADM_EMPTY_FILE,
                                      scratch_pool),
                    TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      ADM_README,
                                      scratch_pool),
                    TRUE, scratch_pool));

  /* For formats <= SVN_WC__WCPROPS_MANY_FILES_VERSION, we toss the wcprops
     for the directory itself, and then all the wcprops for the files.  */
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      WCPROPS_FNAME_FOR_DIR,
                                      scratch_pool),
                    TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_dir2(
                    svn_wc__adm_child(wcroot_abspath,
                                      WCPROPS_SUBDIR_FOR_FILES,
                                      scratch_pool),
                    FALSE, NULL, NULL, scratch_pool));

  /* And for later formats, they are aggregated into one file.  */
  svn_error_clear(svn_io_remove_file2(
                    svn_wc__adm_child(wcroot_abspath,
                                      WCPROPS_ALL_DATA,
                                      scratch_pool),
                    TRUE, scratch_pool));

  /* Remove the old text-base directory and the old text-base files. */
  svn_error_clear(svn_io_remove_dir2(
                    svn_wc__adm_child(wcroot_abspath,
                                      TEXT_BASE_SUBDIR,
                                      scratch_pool),
                    FALSE, NULL, NULL, scratch_pool));

  /* Remove the old properties files... whole directories at a time.  */
  svn_error_clear(svn_io_remove_dir2(
                    svn_wc__adm_child(wcroot_abspath,
                                      PROPS_SUBDIR,
                                      scratch_pool),
                    FALSE, NULL, NULL, scratch_pool));
  svn_error_clear(svn_io_remove_dir2(
                    svn_wc__adm_child(wcroot_abspath,
                                      PROP_BASE_SUBDIR,
                                      scratch_pool),
                    FALSE, NULL, NULL, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                     svn_wc__adm_child(wcroot_abspath,
                                       PROP_WORKING_FOR_DIR,
                                       scratch_pool),
                     TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                     svn_wc__adm_child(wcroot_abspath,
                                      PROP_BASE_FOR_DIR,
                                      scratch_pool),
                     TRUE, scratch_pool));
  svn_error_clear(svn_io_remove_file2(
                     svn_wc__adm_child(wcroot_abspath,
                                      PROP_REVERT_FOR_DIR,
                                      scratch_pool),
                     TRUE, scratch_pool));

#if 0
  /* ### this checks for a write-lock, and we are not (always) taking out
     ### a write lock in all callers.  */
  SVN_ERR(svn_wc__adm_cleanup_tmp_area(db, wcroot_abspath, iterpool));
#endif

  /* Remove the old-style lock file LAST.  */
  svn_error_clear(svn_io_remove_file2(
                    build_lockfile_path(wcroot_abspath, scratch_pool),
                    TRUE, scratch_pool));
}