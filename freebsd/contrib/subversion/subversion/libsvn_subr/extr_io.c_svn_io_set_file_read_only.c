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

/* Variables and functions */
 scalar_t__ APR_ENOTIMPL ; 
 int /*<<< orphan*/  APR_FILE_ATTR_READONLY ; 
 scalar_t__ APR_STATUS_IS_ENOENT (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_ENOTDIR (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_attrs_set (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * io_set_file_perms (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_io_set_file_read_only(const char *path,
                          svn_boolean_t ignore_enoent,
                          apr_pool_t *pool)
{
  /* On Windows and OS/2, just set the file attributes -- on unix call
     our internal function which attempts to honor the umask. */
#if !defined(WIN32) && !defined(__OS2__)
  return io_set_file_perms(path, TRUE, FALSE, FALSE, FALSE,
                           ignore_enoent, pool);
#else
  apr_status_t status;
  const char *path_apr;

  SVN_ERR(cstring_from_utf8(&path_apr, path, pool));

  status = apr_file_attrs_set(path_apr,
                              APR_FILE_ATTR_READONLY,
                              APR_FILE_ATTR_READONLY,
                              pool);

  if (status && status != APR_ENOTIMPL)
    if (!(ignore_enoent && (APR_STATUS_IS_ENOENT(status)
                            || SVN__APR_STATUS_IS_ENOTDIR(status))))
      return svn_error_wrap_apr(status,
                                _("Can't set file '%s' read-only"),
                                svn_dirent_local_style(path, pool));

  return SVN_NO_ERROR;
#endif
}