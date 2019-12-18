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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_empty_tmp_file(const char **tmp_filename,
                   svn_wc__db_t *db,
                   const char *wri_abspath,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  const char *temp_dir_abspath;

  SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&temp_dir_abspath, db, wri_abspath,
                                         scratch_pool, scratch_pool));
  SVN_ERR(svn_io_open_unique_file3(NULL, tmp_filename, temp_dir_abspath,
                                   svn_io_file_del_none,
                                   scratch_pool, scratch_pool));

  return SVN_NO_ERROR;
}