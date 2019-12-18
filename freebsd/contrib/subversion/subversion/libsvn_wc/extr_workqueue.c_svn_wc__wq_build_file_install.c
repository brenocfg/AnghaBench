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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* OP_FILE_INSTALL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_to_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__wq_build_file_install(svn_skel_t **work_item,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              const char *source_abspath,
                              svn_boolean_t use_commit_times,
                              svn_boolean_t record_fileinfo,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  const char *local_relpath;
  const char *wri_abspath;
  *work_item = svn_skel__make_empty_list(result_pool);

  /* Use the directory of the file to install as wri_abspath to avoid
     filestats on just obtaining the wc-root */
  wri_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  /* If a SOURCE_ABSPATH was provided, then put it into the skel. If this
     value is not provided, then the file's pristine contents will be used. */
  if (source_abspath != NULL)
    {
      SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, wri_abspath,
                                    source_abspath,
                                    result_pool, scratch_pool));

      svn_skel__prepend_str(local_relpath, *work_item, result_pool);
    }

  SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, wri_abspath,
                                local_abspath, result_pool, scratch_pool));

  svn_skel__prepend_int(record_fileinfo, *work_item, result_pool);
  svn_skel__prepend_int(use_commit_times, *work_item, result_pool);
  svn_skel__prepend_str(local_relpath, *work_item, result_pool);
  svn_skel__prepend_str(OP_FILE_INSTALL, *work_item, result_pool);

  return SVN_NO_ERROR;
}