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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_baton {TYPE_1__* repos; int /*<<< orphan*/  commit_baton; int /*<<< orphan*/  commit_cb; int /*<<< orphan*/  txn_name; int /*<<< orphan*/  inner; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  hooks_env_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_POST_COMMIT_HOOK_FAILED ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  invoke_commit_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__editor_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos__hooks_post_commit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__hooks_pre_commit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__parse_hooks_env (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_repos__post_commit_error_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
complete_cb(void *baton,
            apr_pool_t *scratch_pool)
{
  struct ev2_baton *eb = baton;
  svn_revnum_t revision;
  svn_error_t *post_commit_err;
  const char *conflict_path;
  svn_error_t *err;
  const char *post_commit_errstr;
  apr_hash_t *hooks_env;

  /* Parse the hooks-env file (if any). */
  SVN_ERR(svn_repos__parse_hooks_env(&hooks_env, eb->repos->hooks_env_path,
                                     scratch_pool, scratch_pool));

  /* The transaction has been fully edited. Let the pre-commit hook
     have a look at the thing.  */
  SVN_ERR(svn_repos__hooks_pre_commit(eb->repos, hooks_env,
                                      eb->txn_name, scratch_pool));

  /* Hook is done. Let's do the actual commit.  */
  SVN_ERR(svn_fs__editor_commit(&revision, &post_commit_err, &conflict_path,
                                eb->inner, scratch_pool, scratch_pool));

  /* Did a conflict occur during the commit process?  */
  if (conflict_path != NULL)
    return svn_error_createf(SVN_ERR_FS_CONFLICT, NULL,
                             _("Conflict at '%s'"), conflict_path);

  /* Since did not receive an error during the commit process, and no
     conflict was specified... we committed a revision. Run the hooks.
     Other errors may have occurred within the FS (specified by the
     POST_COMMIT_ERR localvar), but we need to run the hooks.  */
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(revision));
  err = svn_repos__hooks_post_commit(eb->repos, hooks_env, revision,
                                     eb->txn_name, scratch_pool);
  if (err)
    err = svn_error_create(SVN_ERR_REPOS_POST_COMMIT_HOOK_FAILED, err,
                           _("Commit succeeded, but post-commit hook failed"));

  /* Combine the FS errors with the hook errors, and stringify.  */
  err = svn_error_compose_create(post_commit_err, err);
  if (err)
    {
      post_commit_errstr = svn_repos__post_commit_error_str(err, scratch_pool);
      svn_error_clear(err);
    }
  else
    {
      post_commit_errstr = NULL;
    }

  return svn_error_trace(invoke_commit_cb(eb->commit_cb, eb->commit_baton,
                                          eb->repos->fs, revision,
                                          post_commit_errstr,
                                          scratch_pool));
}