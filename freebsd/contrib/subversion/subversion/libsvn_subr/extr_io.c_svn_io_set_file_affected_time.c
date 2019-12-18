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
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_mtime_set (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_io_set_file_affected_time(apr_time_t apr_time,
                              const char *path,
                              apr_pool_t *pool)
{
  apr_status_t status;
  const char *native_path;

  SVN_ERR(cstring_from_utf8(&native_path, path, pool));
  status = apr_file_mtime_set(native_path, apr_time, pool);

  if (status)
    return svn_error_wrap_apr(status, _("Can't set access time of '%s'"),
                              svn_dirent_local_style(path, pool));

  return SVN_NO_ERROR;
}