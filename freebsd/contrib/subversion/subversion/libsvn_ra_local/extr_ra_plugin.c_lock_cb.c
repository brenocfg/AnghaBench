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
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct lock_baton_t {int /*<<< orphan*/  is_lock; int /*<<< orphan*/  lock_baton; scalar_t__ (* lock_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ cb_err; int /*<<< orphan*/  fs_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
lock_cb(void *lock_baton,
        const char *path,
        const svn_lock_t *lock,
        svn_error_t *fs_err,
        apr_pool_t *pool)
{
  struct lock_baton_t *b = lock_baton;

  if (b && !b->cb_err && b->lock_func)
    {
      path = svn_fspath__skip_ancestor(b->fs_path, path);
      b->cb_err = b->lock_func(b->lock_baton, path, b->is_lock, lock, fs_err,
                               pool);
    }

  return SVN_NO_ERROR;
}