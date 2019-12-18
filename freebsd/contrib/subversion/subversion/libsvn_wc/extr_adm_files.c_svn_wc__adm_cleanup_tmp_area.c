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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_WC__ADM_TMP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_adm_tmp_area (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__write_check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__adm_cleanup_tmp_area(svn_wc__db_t *db,
                             const char *adm_abspath,
                             apr_pool_t *scratch_pool)
{
  const char *tmp_path;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(adm_abspath));

  SVN_ERR(svn_wc__write_check(db, adm_abspath, scratch_pool));

  /* Get the path to the tmp area, and blow it away. */
  tmp_path = svn_wc__adm_child(adm_abspath, SVN_WC__ADM_TMP, scratch_pool);

  SVN_ERR(svn_io_remove_dir2(tmp_path, TRUE, NULL, NULL, scratch_pool));

  /* Now, rebuild the tmp area. */
  return svn_error_trace(init_adm_tmp_area(adm_abspath, scratch_pool));
}