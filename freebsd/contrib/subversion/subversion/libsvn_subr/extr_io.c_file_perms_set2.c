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
typedef  int /*<<< orphan*/  apr_fileperms_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_name_get (char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_perms_set (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  try_utf8_from_internal_style (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
file_perms_set2(apr_file_t* file, apr_fileperms_t perms, apr_pool_t *pool)
{
  const char *fname_apr;
  apr_status_t status;

  status = apr_file_name_get(&fname_apr, file);
  if (status)
    return svn_error_wrap_apr(status, _("Can't get file name"));

  status = apr_file_perms_set(fname_apr, perms);
  if (status)
    return svn_error_wrap_apr(status, _("Can't set permissions on '%s'"),
                              try_utf8_from_internal_style(fname_apr, pool));
  else
    return SVN_NO_ERROR;
}