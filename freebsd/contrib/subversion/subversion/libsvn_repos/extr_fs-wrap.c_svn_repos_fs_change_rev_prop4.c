#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  hooks_env_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  scalar_t__ svn_repos_revision_access_level_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNREADABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_change_rev_prop2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_prop2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__hooks_post_revprop_change (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const*,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__hooks_pre_revprop_change (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const*,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__parse_hooks_env (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__validate_prop (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_check_revision_access (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_revision_access_full ; 

svn_error_t *
svn_repos_fs_change_rev_prop4(svn_repos_t *repos,
                              svn_revnum_t rev,
                              const char *author,
                              const char *name,
                              const svn_string_t *const *old_value_p,
                              const svn_string_t *new_value,
                              svn_boolean_t use_pre_revprop_change_hook,
                              svn_boolean_t use_post_revprop_change_hook,
                              svn_repos_authz_func_t authz_read_func,
                              void *authz_read_baton,
                              apr_pool_t *pool)
{
  svn_repos_revision_access_level_t readability;

  SVN_ERR(svn_repos_check_revision_access(&readability, repos, rev,
                                          authz_read_func, authz_read_baton,
                                          pool));

  if (readability == svn_repos_revision_access_full)
    {
      const svn_string_t *old_value;
      char action;
      apr_hash_t *hooks_env;

      SVN_ERR(svn_repos__validate_prop(name, new_value, pool));

      /* Fetch OLD_VALUE for svn_fs_change_rev_prop2(). */
      if (old_value_p)
        {
          old_value = *old_value_p;
        }
      else
        {
          /* Get OLD_VALUE anyway, in order for ACTION and OLD_VALUE arguments
           * to the hooks to be accurate. */
          svn_string_t *old_value2;

          SVN_ERR(svn_fs_revision_prop2(&old_value2, repos->fs, rev, name,
                                        TRUE, pool, pool));
          old_value = old_value2;
        }

      /* Prepare ACTION. */
      if (! new_value)
        action = 'D';
      else if (! old_value)
        action = 'A';
      else
        action = 'M';

      /* Parse the hooks-env file (if any, and if to be used). */
      if (use_pre_revprop_change_hook || use_post_revprop_change_hook)
        SVN_ERR(svn_repos__parse_hooks_env(&hooks_env, repos->hooks_env_path,
                                           pool, pool));

      /* ### currently not passing the old_value to hooks */
      if (use_pre_revprop_change_hook)
        SVN_ERR(svn_repos__hooks_pre_revprop_change(repos, hooks_env, rev,
                                                    author, name, new_value,
                                                    action, pool));

      SVN_ERR(svn_fs_change_rev_prop2(repos->fs, rev, name,
                                      &old_value, new_value, pool));

      if (use_post_revprop_change_hook)
        SVN_ERR(svn_repos__hooks_post_revprop_change(repos, hooks_env, rev,
                                                     author, name, old_value,
                                                     action, pool));
    }
  else  /* rev is either unreadable or only partially readable */
    {
      return svn_error_createf
        (SVN_ERR_AUTHZ_UNREADABLE, NULL,
         _("Write denied:  not authorized to read all of revision %ld"), rev);
    }

  return SVN_NO_ERROR;
}