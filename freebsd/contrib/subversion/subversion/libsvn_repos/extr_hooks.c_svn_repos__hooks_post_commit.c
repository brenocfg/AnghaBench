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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS__HOOK_POST_COMMIT ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* check_hook_cmd (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hook_symlink_error (char const*) ; 
 int /*<<< orphan*/  run_hook_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_repos_post_commit_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t  *
svn_repos__hooks_post_commit(svn_repos_t *repos,
                             apr_hash_t *hooks_env,
                             svn_revnum_t rev,
                             const char *txn_name,
                             apr_pool_t *pool)
{
  const char *hook = svn_repos_post_commit_hook(repos, pool);
  svn_boolean_t broken_link;

  if ((hook = check_hook_cmd(hook, &broken_link, pool)) && broken_link)
    {
      return hook_symlink_error(hook);
    }
  else if (hook)
    {
      const char *args[5];

      args[0] = hook;
      args[1] = svn_dirent_local_style(svn_repos_path(repos, pool), pool);
      args[2] = apr_psprintf(pool, "%ld", rev);
      args[3] = txn_name;
      args[4] = NULL;

      SVN_ERR(run_hook_cmd(NULL, SVN_REPOS__HOOK_POST_COMMIT, hook, args,
                           hooks_env, NULL, pool));
    }

  return SVN_NO_ERROR;
}