#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/  TRUE ; 
 char* nonexistent_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_close (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_get_wcroot (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__text_base_path_to_read (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_pristine_copy_path(const char *path,
                              const char **pristine_path,
                              apr_pool_t *pool)
{
  svn_wc__db_t *db;
  const char *local_abspath;
  svn_error_t *err;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  SVN_ERR(svn_wc__db_open(&db, NULL, FALSE, TRUE, pool, pool));
  /* DB is now open. This is seemingly a "light" function that a caller
     may use repeatedly despite error return values. The rest of this
     function should aggressively close DB, even in the error case.  */

  err = svn_wc__text_base_path_to_read(pristine_path, db, local_abspath,
                                       pool, pool);
  if (err && err->apr_err == SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
    {
      /* The node doesn't exist, so return a non-existent path located
         in WCROOT/.svn/  */
      const char *wcroot_abspath;

      svn_error_clear(err);

      err = svn_wc__db_get_wcroot(&wcroot_abspath, db, local_abspath,
                                  pool, pool);
      if (err == NULL)
        *pristine_path = nonexistent_path(wcroot_abspath, pool);
    }

   return svn_error_compose_create(err, svn_wc__db_close(db));
}