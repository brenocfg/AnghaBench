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
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int APR_EXCL ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 int APR_WRITE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* build_lockfile_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_physical_lock(const char *abspath, apr_pool_t *scratch_pool)
{
  const char *lock_abspath = build_lockfile_path(abspath, scratch_pool);
  svn_error_t *err;
  apr_file_t *file;

  err = svn_io_file_open(&file, lock_abspath,
                         APR_WRITE | APR_CREATE | APR_EXCL,
                         APR_OS_DEFAULT,
                         scratch_pool);

  if (err && APR_STATUS_IS_EEXIST(err->apr_err))
    {
      /* Congratulations, we just stole a physical lock from somebody */
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }

  return svn_error_trace(err);
}