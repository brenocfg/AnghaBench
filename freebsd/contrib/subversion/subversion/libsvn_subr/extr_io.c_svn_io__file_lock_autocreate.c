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
 scalar_t__ APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_io_file_create_empty (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_file_lock2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io__file_lock_autocreate(const char *lock_file,
                             apr_pool_t *pool)
{
  svn_error_t *err
    = svn_io_file_lock2(lock_file, TRUE, FALSE, pool);
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      /* No lock file?  No big deal; these are just empty files anyway.
         Create it and try again. */
      svn_error_clear(err);

      /* This file creation is racy.
         We don't care as long as file gets created at all. */
      err = svn_io_file_create_empty(lock_file, pool);
      if (err && APR_STATUS_IS_EEXIST(err->apr_err))
        {
          svn_error_clear(err);
          err = NULL;
        }

      /* Finally, lock the file - if it exists */
      if (!err)
        err = svn_io_file_lock2(lock_file, TRUE, FALSE, pool);
    }

  return svn_error_trace(err);
}