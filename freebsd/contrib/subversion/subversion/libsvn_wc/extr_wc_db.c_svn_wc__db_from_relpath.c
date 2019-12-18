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
 int /*<<< orphan*/  CHECK_MINIMAL_WCROOT (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_from_relpath(const char **local_abspath,
                        svn_wc__db_t *db,
                        const char *wri_abspath,
                        const char *local_relpath,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *unused_relpath;
#if 0
  SVN_ERR_ASSERT(svn_relpath_is_canonical(local_relpath));
#endif

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &unused_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));

  /* This function is indirectly called from the upgrade code, so we
     can't verify the wcroot here. Just check that it is not NULL */
  CHECK_MINIMAL_WCROOT(wcroot, wri_abspath, scratch_pool);


  *local_abspath = svn_dirent_join(wcroot->abspath,
                                   local_relpath,
                                   result_pool);
  return SVN_NO_ERROR;
}