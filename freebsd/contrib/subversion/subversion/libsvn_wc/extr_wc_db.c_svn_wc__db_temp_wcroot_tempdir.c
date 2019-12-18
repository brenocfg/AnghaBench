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
struct TYPE_4__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  WCROOT_TEMPDIR_RELPATH ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_dirent_join_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_adm_dir (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_temp_wcroot_tempdir(const char **temp_dir_abspath,
                               svn_wc__db_t *db,
                               const char *wri_abspath,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;

  SVN_ERR_ASSERT(temp_dir_abspath != NULL);
  SVN_ERR_ASSERT(svn_dirent_is_absolute(wri_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  *temp_dir_abspath = svn_dirent_join_many(result_pool,
                                           wcroot->abspath,
                                           svn_wc_get_adm_dir(scratch_pool),
                                           WCROOT_TEMPDIR_RELPATH,
                                           SVN_VA_NULL);
  return SVN_NO_ERROR;
}