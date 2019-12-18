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
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_locks_callback ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_fs_base__get_lock_helper (int /*<<< orphan*/ **,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__locks_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__allow_locked_operation(const char *path,
                                    svn_boolean_t recurse,
                                    trail_t *trail,
                                    apr_pool_t *pool)
{
  if (recurse)
    {
      /* Discover all locks at or below the path. */
      SVN_ERR(svn_fs_bdb__locks_get(trail->fs, path, svn_depth_infinity,
                                    get_locks_callback,
                                    trail->fs, trail, pool));
    }
  else
    {
      svn_lock_t *lock;

      /* Discover any lock attached to the path. */
      SVN_ERR(svn_fs_base__get_lock_helper(&lock, path, trail, pool));
      if (lock)
        SVN_ERR(verify_lock(trail->fs, lock, pool));
    }
  return SVN_NO_ERROR;
}