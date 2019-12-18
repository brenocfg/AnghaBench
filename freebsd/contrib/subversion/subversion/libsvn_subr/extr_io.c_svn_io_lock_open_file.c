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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
#define  APR_FLOCK_EXCLUSIVE 129 
 int APR_FLOCK_NONBLOCK ; 
#define  APR_FLOCK_SHARED 128 
 int APR_FLOCK_TYPEMASK ; 
 int /*<<< orphan*/  FILE_LOCK_RETRY_LOOP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_lock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_file_name_get (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_clear_locks ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  try_utf8_from_internal_style (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_lock_open_file(apr_file_t *lockfile_handle,
                      svn_boolean_t exclusive,
                      svn_boolean_t nonblocking,
                      apr_pool_t *pool)
{
  int locktype = APR_FLOCK_SHARED;
  apr_status_t apr_err;
  const char *fname;

  if (exclusive)
    locktype = APR_FLOCK_EXCLUSIVE;
  if (nonblocking)
    locktype |= APR_FLOCK_NONBLOCK;

  /* We need this only in case of an error but this is cheap to get -
   * so we do it here for clarity. */
  apr_err = apr_file_name_get(&fname, lockfile_handle);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't get file name"));

  /* Get lock on the filehandle. */
  apr_err = apr_file_lock(lockfile_handle, locktype);

  /* In deployments with two or more multithreaded servers running on
     the same system serving two or more fsfs repositories it is
     possible for a deadlock to occur when getting a write lock on
     db/txn-current-lock:

     Process 1                         Process 2
     ---------                         ---------
     thread 1: get lock in repos A
                                       thread 1: get lock in repos B
                                       thread 2: block getting lock in repos A
     thread 2: try to get lock in B *** deadlock ***

     Retry for a while for the deadlock to clear. */
  FILE_LOCK_RETRY_LOOP(apr_err, apr_file_lock(lockfile_handle, locktype));

  if (apr_err)
    {
      switch (locktype & APR_FLOCK_TYPEMASK)
        {
        case APR_FLOCK_SHARED:
          return svn_error_wrap_apr(apr_err,
                                    _("Can't get shared lock on file '%s'"),
                                    try_utf8_from_internal_style(fname, pool));
        case APR_FLOCK_EXCLUSIVE:
          return svn_error_wrap_apr(apr_err,
                                    _("Can't get exclusive lock on file '%s'"),
                                    try_utf8_from_internal_style(fname, pool));
        default:
          SVN_ERR_MALFUNCTION();
        }
    }

  /* On Windows, a process may not release file locks before closing the
     handle, and in this case the outstanding locks are unlocked by the OS.
     However, this is not recommended, because the actual unlocking may be
     postponed depending on available system resources.  We explicitly unlock
     the file as a part of the pool cleanup handler. */
  apr_pool_cleanup_register(pool, lockfile_handle,
                            file_clear_locks,
                            apr_pool_cleanup_null);

  return SVN_NO_ERROR;
}