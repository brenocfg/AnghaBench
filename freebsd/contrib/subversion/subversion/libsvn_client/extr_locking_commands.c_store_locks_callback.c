#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  url; void* lock_state; int /*<<< orphan*/  path_prefix; TYPE_3__* err; int /*<<< orphan*/  const* lock; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct lock_baton {TYPE_1__* ctx; int /*<<< orphan*/  base_url; int /*<<< orphan*/  pool; int /*<<< orphan*/  base_dir_abspath; scalar_t__ urls_to_paths; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_LOCK_OWNER_MISMATCH ; 
 scalar_t__ SVN_ERR_REPOS_HOOK_FAILURE ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_lock2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_failed_lock ; 
 int /*<<< orphan*/  svn_wc_notify_failed_unlock ; 
 void* svn_wc_notify_lock_state_locked ; 
 void* svn_wc_notify_lock_state_unchanged ; 
 void* svn_wc_notify_lock_state_unlocked ; 
 int /*<<< orphan*/  svn_wc_notify_locked ; 
 int /*<<< orphan*/  svn_wc_notify_unlocked ; 
 int /*<<< orphan*/  svn_wc_remove_lock2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
store_locks_callback(void *baton,
                     const char *rel_url,
                     svn_boolean_t do_lock,
                     const svn_lock_t *lock,
                     svn_error_t *ra_err, apr_pool_t *pool)
{
  struct lock_baton *lb = baton;
  svn_wc_notify_t *notify;
  const char *local_abspath = lb->urls_to_paths
                                  ? svn_hash_gets(lb->urls_to_paths, rel_url)
                                  : NULL;

  /* Create the notify struct first, so we can tweak it below. */
  notify = svn_wc_create_notify(local_abspath ? local_abspath : rel_url,
                                do_lock
                                ? (ra_err
                                   ? svn_wc_notify_failed_lock
                                   : svn_wc_notify_locked)
                                : (ra_err
                                   ? svn_wc_notify_failed_unlock
                                   : svn_wc_notify_unlocked),
                                pool);
  notify->lock = lock;
  notify->err = ra_err;

  if (local_abspath)
    {
      /* Notify a valid working copy path */
      notify->path_prefix = lb->base_dir_abspath;

      if (do_lock)
        {
          if (!ra_err && lock)
            {
              SVN_ERR(svn_wc_add_lock2(lb->ctx->wc_ctx, local_abspath, lock,
                                       lb->pool));
              notify->lock_state = svn_wc_notify_lock_state_locked;
            }
          else
            notify->lock_state = svn_wc_notify_lock_state_unchanged;
        }
      else /* unlocking */
        {
          /* Remove our wc lock token either a) if we got no error, or b) if
             we got any error except for owner mismatch or hook failure (the
             hook would be pre-unlock rather than post-unlock). Note that the
             only errors that are handed to this callback will be
             locking-related errors. */

          if (!ra_err ||
              (ra_err && (ra_err->apr_err != SVN_ERR_FS_LOCK_OWNER_MISMATCH
                          && ra_err->apr_err != SVN_ERR_REPOS_HOOK_FAILURE)))
            {
              SVN_ERR(svn_wc_remove_lock2(lb->ctx->wc_ctx, local_abspath,
                                          lb->pool));
              notify->lock_state = svn_wc_notify_lock_state_unlocked;
            }
          else
            notify->lock_state = svn_wc_notify_lock_state_unchanged;
        }
    }
  else
    notify->url = svn_path_url_add_component2(lb->base_url, rel_url, pool);

  if (lb->ctx->notify_func2)
    lb->ctx->notify_func2(lb->ctx->notify_baton2, notify, pool);

  return SVN_NO_ERROR;
}