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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_name_get (char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_clear_locks ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  try_utf8_from_internal_style (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_unlock_open_file(apr_file_t *lockfile_handle,
                        apr_pool_t *pool)
{
  const char *fname;
  apr_status_t apr_err;

  /* We need this only in case of an error but this is cheap to get -
   * so we do it here for clarity. */
  apr_err = apr_file_name_get(&fname, lockfile_handle);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't get file name"));

  /* The actual unlock attempt. */
  apr_err = apr_file_unlock(lockfile_handle);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't unlock file '%s'"),
                              try_utf8_from_internal_style(fname, pool));

  apr_pool_cleanup_kill(pool, lockfile_handle, file_clear_locks);

  return SVN_NO_ERROR;
}