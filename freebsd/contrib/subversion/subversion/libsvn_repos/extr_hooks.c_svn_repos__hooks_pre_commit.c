#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_NULL_DEVICE_NAME ; 
 int /*<<< orphan*/  SVN_REPOS__HOOK_PRE_COMMIT ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 char* check_hook_cmd (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hook_symlink_error (char const*) ; 
 int /*<<< orphan*/  lock_token_content (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_hook_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs__access_get_lock_tokens (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_get_access (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_repos_pre_commit_hook (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t  *
svn_repos__hooks_pre_commit(svn_repos_t *repos,
                            apr_hash_t *hooks_env,
                            const char *txn_name,
                            apr_pool_t *pool)
{
  const char *hook = svn_repos_pre_commit_hook(repos, pool);
  svn_boolean_t broken_link;

  if ((hook = check_hook_cmd(hook, &broken_link, pool)) && broken_link)
    {
      return hook_symlink_error(hook);
    }
  else if (hook)
    {
      const char *args[4];
      svn_fs_access_t *access_ctx;
      apr_file_t *stdin_handle = NULL;

      args[0] = hook;
      args[1] = svn_dirent_local_style(svn_repos_path(repos, pool), pool);
      args[2] = txn_name;
      args[3] = NULL;

      SVN_ERR(svn_fs_get_access(&access_ctx, repos->fs));
      if (access_ctx)
        {
          apr_hash_t *lock_tokens = svn_fs__access_get_lock_tokens(access_ctx);
          if (apr_hash_count(lock_tokens))  {
            SVN_ERR(lock_token_content(&stdin_handle, lock_tokens, pool));
          }
        }

      if (!stdin_handle)
        SVN_ERR(svn_io_file_open(&stdin_handle, SVN_NULL_DEVICE_NAME,
                                 APR_READ, APR_OS_DEFAULT, pool));

      SVN_ERR(run_hook_cmd(NULL, SVN_REPOS__HOOK_PRE_COMMIT, hook, args,
                           hooks_env, stdin_handle, pool));
    }

  return SVN_NO_ERROR;
}