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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct lock_baton_t {int /*<<< orphan*/ * fs_err; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_cb ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_unlock_many (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 

svn_error_t *
svn_fs_unlock(svn_fs_t *fs, const char *path, const char *token,
              svn_boolean_t break_lock, apr_pool_t *pool)
{
  apr_hash_t *targets = apr_hash_make(pool);
  svn_error_t *err;
  struct lock_baton_t baton = {0};

  if (!token)
    token = "";
  svn_hash_sets(targets, path, token);

  err = svn_fs_unlock_many(fs, targets, break_lock, lock_cb, &baton,
                           pool, pool);

  if (err && baton.fs_err)
    svn_error_compose(err, baton.fs_err);
  else if (!err)
    err = baton.fs_err;

  return svn_error_trace(err);
}