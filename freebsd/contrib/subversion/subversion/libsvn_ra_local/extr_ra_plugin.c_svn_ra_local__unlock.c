#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_lock_callback_t ;
struct TYPE_8__ {int /*<<< orphan*/  repos; TYPE_1__* fs_path; } ;
typedef  TYPE_3__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct lock_baton_t {int /*<<< orphan*/ * cb_err; int /*<<< orphan*/  is_lock; int /*<<< orphan*/  fs_path; void* lock_baton; int /*<<< orphan*/  lock_func; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_username (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_cb ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * svn_repos_fs_unlock_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__unlock(svn_ra_session_t *session,
                     apr_hash_t *path_tokens,
                     svn_boolean_t force,
                     svn_ra_lock_callback_t lock_func,
                     void *lock_baton,
                     apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;
  apr_hash_t *targets = apr_hash_make(pool);
  apr_hash_index_t *hi;
  svn_error_t *err;
  struct lock_baton_t baton = {0};

  /* A username is absolutely required to unlock a path. */
  SVN_ERR(get_username(session, pool));

  for (hi = apr_hash_first(pool, path_tokens); hi; hi = apr_hash_next(hi))
    {
      const char *abs_path = svn_fspath__join(sess->fs_path->data,
                                              apr_hash_this_key(hi), pool);
      const char *token = apr_hash_this_val(hi);

      svn_hash_sets(targets, abs_path, token);
    }

  baton.lock_func = lock_func;
  baton.lock_baton = lock_baton;
  baton.fs_path = sess->fs_path->data;
  baton.is_lock = FALSE;
  baton.cb_err = SVN_NO_ERROR;

  err = svn_repos_fs_unlock_many(sess->repos, targets, force, lock_cb, &baton,
                                 pool, pool);

  if (err && baton.cb_err)
    svn_error_compose(err, baton.cb_err);
  else if (!err)
    err = baton.cb_err;

  return svn_error_trace(err);
}