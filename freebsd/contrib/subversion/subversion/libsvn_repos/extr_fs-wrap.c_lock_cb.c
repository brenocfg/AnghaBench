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
struct lock_baton_t {int /*<<< orphan*/  fs_err; int /*<<< orphan*/  const* lock; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_dup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
lock_cb(void *lock_baton,
        const char *path,
        const svn_lock_t *lock,
        svn_error_t *fs_err,
        apr_pool_t *pool)
{
  struct lock_baton_t *b = lock_baton;

  b->lock = lock;
  b->fs_err = svn_error_dup(fs_err);

  return SVN_NO_ERROR;
}