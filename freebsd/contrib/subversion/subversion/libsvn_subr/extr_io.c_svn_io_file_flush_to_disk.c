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
typedef  int /*<<< orphan*/  apr_os_file_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EINTR (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_EINVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_FULLFSYNC ; 
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_name_get (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_get_os_error () ; 
 int /*<<< orphan*/  apr_os_file_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_io_file_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_utf8_from_internal_style (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *svn_io_file_flush_to_disk(apr_file_t *file,
                                       apr_pool_t *pool)
{
  apr_os_file_t filehand;
  const char *fname;
  apr_status_t apr_err;

  /* We need this only in case of an error but this is cheap to get -
   * so we do it here for clarity. */
  apr_err = apr_file_name_get(&fname, file);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't get file name"));

  /* ### In apr 1.4+ we could delegate most of this function to
         apr_file_sync(). The only major difference is that this doesn't
         contain the retry loop for EINTR on linux. */

  /* First make sure that any user-space buffered data is flushed. */
  SVN_ERR(svn_io_file_flush(file, pool));

  apr_os_file_get(&filehand, file);

  /* Call the operating system specific function to actually force the
     data to disk. */
  {
#ifdef WIN32

    if (! FlushFileBuffers(filehand))
        return svn_error_wrap_apr(apr_get_os_error(),
                                  _("Can't flush file '%s' to disk"),
                                  try_utf8_from_internal_style(fname, pool));

#else
      int rv;

      do {
#ifdef F_FULLFSYNC
        rv = fcntl(filehand, F_FULLFSYNC, 0);
#else
        rv = fsync(filehand);
#endif
      } while (rv == -1 && APR_STATUS_IS_EINTR(apr_get_os_error()));

      /* If the file is in a memory filesystem, fsync() may return
         EINVAL.  Presumably the user knows the risks, and we can just
         ignore the error. */
      if (rv == -1 && APR_STATUS_IS_EINVAL(apr_get_os_error()))
        return SVN_NO_ERROR;

      if (rv == -1)
        return svn_error_wrap_apr(apr_get_os_error(),
                                  _("Can't flush file '%s' to disk"),
                                  try_utf8_from_internal_style(fname, pool));

#endif
  }
  return SVN_NO_ERROR;
}