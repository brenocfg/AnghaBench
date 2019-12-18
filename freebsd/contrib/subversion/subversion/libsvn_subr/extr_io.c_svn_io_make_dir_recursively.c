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

/* Variables and functions */
 scalar_t__ APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  WIN32_RETRY_LOOP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_dir_make_recursive (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 

svn_error_t *
svn_io_make_dir_recursively(const char *path, apr_pool_t *pool)
{
  const char *path_apr;
  apr_status_t apr_err;

  if (svn_path_is_empty(path))
    /* Empty path (current dir) is assumed to always exist,
       so we do nothing, per docs. */
    return SVN_NO_ERROR;

  SVN_ERR(cstring_from_utf8(&path_apr, path, pool));

  apr_err = apr_dir_make_recursive(path_apr, APR_OS_DEFAULT, pool);
#ifdef WIN32
  /* Don't retry on ERROR_ACCESS_DENIED, as that typically signals a
     permanent error */
  if (apr_err == APR_FROM_OS_ERROR(ERROR_SHARING_VIOLATION))
    WIN32_RETRY_LOOP(apr_err, apr_dir_make_recursive(path_apr,
                                                     APR_OS_DEFAULT, pool));
#endif

  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't make directory '%s'"),
                              svn_dirent_local_style(path, pool));

  return SVN_NO_ERROR;
}