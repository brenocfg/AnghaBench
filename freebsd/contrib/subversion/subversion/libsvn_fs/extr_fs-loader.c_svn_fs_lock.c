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
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_3__ {char const* token; int /*<<< orphan*/  current_rev; } ;
typedef  TYPE_1__ svn_fs_lock_target_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct lock_baton_t {int /*<<< orphan*/ * fs_err; scalar_t__ lock; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_cb ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_lock_many (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

svn_error_t *
svn_fs_lock(svn_lock_t **lock, svn_fs_t *fs, const char *path,
            const char *token, const char *comment,
            svn_boolean_t is_dav_comment, apr_time_t expiration_date,
            svn_revnum_t current_rev, svn_boolean_t steal_lock,
            apr_pool_t *pool)
{
  apr_hash_t *targets = apr_hash_make(pool);
  svn_fs_lock_target_t target;
  svn_error_t *err;
  struct lock_baton_t baton = {0};

  target.token = token;
  target.current_rev = current_rev;
  svn_hash_sets(targets, path, &target);

  err = svn_fs_lock_many(fs, targets, comment, is_dav_comment,
                         expiration_date, steal_lock, lock_cb, &baton,
                         pool, pool);

  if (baton.lock)
    *lock = (svn_lock_t*)baton.lock;

  if (err && baton.fs_err)
    svn_error_compose(err, baton.fs_err);
  else if (!err)
    err = baton.fs_err;

  return svn_error_trace(err);
}