#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  hooks_env_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_lock_target_t ;
typedef  int /*<<< orphan*/ * (* svn_fs_lock_callback_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct lock_many_baton_t {TYPE_5__* paths; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * cb_err; void* lock_baton; int /*<<< orphan*/ * (* lock_callback ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  need_lock; } ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_USER ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_POST_LOCK_HOOK_FAILED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 TYPE_5__* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_many_cb ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_access_get_username (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_get_access (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_lock_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_many_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_lock_target_set_token (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos__hooks_post_lock (TYPE_1__*,int /*<<< orphan*/ *,TYPE_5__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos__hooks_pre_lock (TYPE_1__*,int /*<<< orphan*/ *,char const**,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__parse_hooks_env (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_lock_many(svn_repos_t *repos,
                       apr_hash_t *targets,
                       const char *comment,
                       svn_boolean_t is_dav_comment,
                       apr_time_t expiration_date,
                       svn_boolean_t steal_lock,
                       svn_fs_lock_callback_t lock_callback,
                       void *lock_baton,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_error_t *err, *cb_err = SVN_NO_ERROR;
  svn_fs_access_t *access_ctx = NULL;
  const char *username = NULL;
  apr_hash_t *hooks_env;
  apr_hash_t *pre_targets = apr_hash_make(scratch_pool);
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  struct lock_many_baton_t baton;

  if (!apr_hash_count(targets))
    return SVN_NO_ERROR;

  /* Parse the hooks-env file (if any). */
  SVN_ERR(svn_repos__parse_hooks_env(&hooks_env, repos->hooks_env_path,
                                     scratch_pool, scratch_pool));

  SVN_ERR(svn_fs_get_access(&access_ctx, repos->fs));
  if (access_ctx)
    SVN_ERR(svn_fs_access_get_username(&username, access_ctx));

  if (! username)
    return svn_error_create
      (SVN_ERR_FS_NO_USER, NULL,
       "Cannot lock path, no authenticated username available.");

  /* Run pre-lock hook.  This could throw error, preventing
     svn_fs_lock2() from happening for that path. */
  for (hi = apr_hash_first(scratch_pool, targets); hi; hi = apr_hash_next(hi))
    {
      const char *new_token;
      svn_fs_lock_target_t *target;
      const char *path = apr_hash_this_key(hi);

      svn_pool_clear(iterpool);

      err = svn_repos__hooks_pre_lock(repos, hooks_env, &new_token, path,
                                      username, comment, steal_lock, iterpool);
      if (err)
        {
          if (!cb_err && lock_callback)
            cb_err = lock_callback(lock_baton, path, NULL, err, iterpool);
          svn_error_clear(err);

          continue;
        }

      target = apr_hash_this_val(hi);
      if (*new_token)
        svn_fs_lock_target_set_token(target, new_token);
      svn_hash_sets(pre_targets, path, target);
    }

  if (!apr_hash_count(pre_targets))
    return svn_error_trace(cb_err);

  baton.need_lock = TRUE;
  baton.paths = apr_array_make(scratch_pool, apr_hash_count(pre_targets),
                               sizeof(const char *));
  baton.lock_callback = lock_callback;
  baton.lock_baton = lock_baton;
  baton.cb_err = cb_err;
  baton.pool = scratch_pool;

  err = svn_fs_lock_many(repos->fs, pre_targets, comment,
                         is_dav_comment, expiration_date, steal_lock,
                         lock_many_cb, &baton, result_pool, iterpool);

  /* If there are locks run the post-lock even if there is an error. */
  if (baton.paths->nelts)
    {
      svn_error_t *perr = svn_repos__hooks_post_lock(repos, hooks_env,
                                                     baton.paths, username,
                                                     iterpool);
      if (perr)
        {
          perr = svn_error_create(SVN_ERR_REPOS_POST_LOCK_HOOK_FAILED, perr,
                            _("Locking succeeded, but post-lock hook failed"));
          err = svn_error_compose_create(err, perr);
        }
    }

  svn_pool_destroy(iterpool);

  if (err && cb_err)
    svn_error_compose(err, cb_err);
  else if (!err)
    err = cb_err;

  return svn_error_trace(err);
}