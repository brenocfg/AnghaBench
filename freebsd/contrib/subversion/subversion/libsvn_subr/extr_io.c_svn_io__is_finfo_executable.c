#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uid_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_gid_t ;
struct TYPE_3__ {int protection; int /*<<< orphan*/  group; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 int APR_GEXECUTE ; 
 scalar_t__ APR_SUCCESS ; 
 int APR_UEXECUTE ; 
 int APR_WEXECUTE ; 
 int FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_gid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_uid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_uid_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_io__is_finfo_executable(svn_boolean_t *executable,
                            apr_finfo_t *file_info,
                            apr_pool_t *pool)
{
#if defined(APR_HAS_USER) && !defined(WIN32) &&!defined(__OS2__)
  apr_status_t apr_err;
  apr_uid_t uid;
  apr_gid_t gid;

  *executable = FALSE;

  apr_err = apr_uid_current(&uid, &gid, pool);

  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Error getting UID of process"));

  /* Check executable bit for current user. */
  if (apr_uid_compare(uid, file_info->user) == APR_SUCCESS)
    *executable = (file_info->protection & APR_UEXECUTE);

  else if (apr_gid_compare(gid, file_info->group) == APR_SUCCESS)
    *executable = (file_info->protection & APR_GEXECUTE);

  else
    *executable = (file_info->protection & APR_WEXECUTE);

#else  /* WIN32 || __OS2__ || !APR_HAS_USER */
  *executable = FALSE;
#endif

  return SVN_NO_ERROR;
}