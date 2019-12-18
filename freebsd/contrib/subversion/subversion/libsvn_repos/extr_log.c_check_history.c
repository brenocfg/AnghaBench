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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct path_info {scalar_t__ history_rev; scalar_t__ done; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_history (struct path_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_history(svn_boolean_t *changed,
              struct path_info *info,
              svn_fs_t *fs,
              svn_revnum_t current,
              svn_boolean_t strict,
              svn_repos_authz_func_t authz_read_func,
              void *authz_read_baton,
              svn_revnum_t start,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  /* If we're already done with histories for this path,
     don't try to fetch any more. */
  if (info->done)
    return SVN_NO_ERROR;

  /* If the last rev we got for this path is less than CURRENT,
     then just return and don't fetch history for this path.
     The caller will get to this rev eventually or else reach
     the limit. */
  if (info->history_rev < current)
    return SVN_NO_ERROR;

  /* If the last rev we got for this path is equal to CURRENT
     then set *CHANGED to true and get the next history
     rev where this path was changed. */
  *changed = TRUE;
  return get_history(info, fs, strict, authz_read_func,
                     authz_read_baton, start, result_pool, scratch_pool);
}