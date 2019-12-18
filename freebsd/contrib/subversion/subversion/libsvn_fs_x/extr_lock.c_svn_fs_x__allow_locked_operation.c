#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  digest_path_from_path (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_lock_helper (TYPE_1__*,int /*<<< orphan*/ **,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_locks_callback ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_locks (TYPE_1__*,char const*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__allow_locked_operation(const char *path,
                                 svn_fs_t *fs,
                                 svn_boolean_t recurse,
                                 svn_boolean_t have_write_lock,
                                 apr_pool_t *scratch_pool)
{
  path = svn_fs__canonicalize_abspath(path, scratch_pool);
  if (recurse)
    {
      /* Discover all locks at or below the path. */
      const char *digest_path;
      SVN_ERR(digest_path_from_path(&digest_path, fs->path, path,
                                    scratch_pool));
      SVN_ERR(walk_locks(fs, digest_path, get_locks_callback,
                         fs, have_write_lock, scratch_pool));
    }
  else
    {
      /* Discover and verify any lock attached to the path. */
      svn_lock_t *lock;
      SVN_ERR(get_lock_helper(fs, &lock, path, have_write_lock,
                              scratch_pool));
      if (lock)
        SVN_ERR(verify_lock(fs, lock));
    }
  return SVN_NO_ERROR;
}