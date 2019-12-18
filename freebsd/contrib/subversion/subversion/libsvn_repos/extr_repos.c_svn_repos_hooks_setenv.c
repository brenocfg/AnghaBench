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
struct TYPE_3__ {int /*<<< orphan*/  pool; void* hooks_env_path; int /*<<< orphan*/  conf_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_REPOS__CONF_HOOKS_ENV ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 void* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_repos_hooks_setenv(svn_repos_t *repos,
                       const char *hooks_env_path,
                       apr_pool_t *scratch_pool)
{
  if (hooks_env_path == NULL)
    repos->hooks_env_path = svn_dirent_join(repos->conf_path,
                                            SVN_REPOS__CONF_HOOKS_ENV,
                                            repos->pool);
  else if (!svn_dirent_is_absolute(hooks_env_path))
    repos->hooks_env_path = svn_dirent_join(repos->conf_path,
                                            hooks_env_path,
                                            repos->pool);
  else
    repos->hooks_env_path = apr_pstrdup(repos->pool, hooks_env_path);

  return SVN_NO_ERROR;
}