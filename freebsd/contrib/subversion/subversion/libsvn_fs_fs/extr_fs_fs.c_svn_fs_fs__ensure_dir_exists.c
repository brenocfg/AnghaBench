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
struct TYPE_8__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__ensure_dir_exists(const char *path,
                             const char *fs_path,
                             apr_pool_t *pool)
{
  svn_error_t *err = svn_io_dir_make(path, APR_OS_DEFAULT, pool);
  if (err && APR_STATUS_IS_EEXIST(err->apr_err))
    {
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

  /* We successfully created a new directory.  Dup the permissions
     from FS->path. */
  return svn_io_copy_perms(fs_path, path, pool);
}