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

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_perms_set (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
file_perms_set(const char *fname, apr_fileperms_t perms,
               apr_pool_t *pool)
{
  const char *fname_apr;
  apr_status_t status;

  SVN_ERR(cstring_from_utf8(&fname_apr, fname, pool));

  status = apr_file_perms_set(fname_apr, perms);
  if (status)
    return svn_error_wrap_apr(status, _("Can't set permissions on '%s'"),
                              fname);
  else
    return SVN_NO_ERROR;
}