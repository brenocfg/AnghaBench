#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ svn_repos_t ;
struct TYPE_12__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_TYPE_BDB ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_io_file_lock2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_repos_db_lockfile (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
lock_repos(svn_repos_t *repos,
           svn_boolean_t exclusive,
           svn_boolean_t nonblocking,
           apr_pool_t *pool)
{
  if (strcmp(repos->fs_type, SVN_FS_TYPE_BDB) == 0)
    {
      svn_error_t *err;
      const char *lockfile_path = svn_repos_db_lockfile(repos, pool);

      err = svn_io_file_lock2(lockfile_path, exclusive, nonblocking, pool);
      if (err != NULL && APR_STATUS_IS_EAGAIN(err->apr_err))
        return svn_error_trace(err);
      SVN_ERR_W(err, _("Error opening db lockfile"));
    }
  return SVN_NO_ERROR;
}