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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  SVN_FS_TYPE_FSFS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_set_warning_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_type (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning_func ; 

svn_error_t *
open_fs(svn_fs_t **fs,
        const char *path,
        apr_pool_t *pool)
{
  const char *fs_type;

  /* Verify that we can handle the repository type. */
  path = svn_dirent_join(path, "db", pool);
  SVN_ERR(svn_fs_type(&fs_type, path, pool));
  if (strcmp(fs_type, SVN_FS_TYPE_FSFS))
    return svn_error_createf(SVN_ERR_FS_UNSUPPORTED_TYPE, NULL,
                             _("%s repositories are not supported"),
                             fs_type);

  /* Now open it. */
  SVN_ERR(svn_fs_open2(fs, path, NULL, pool, pool));
  svn_fs_set_warning_func(*fs, warning_func, NULL);

  return SVN_NO_ERROR;
}