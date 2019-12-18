#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_11__ {int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ svn_lock_t ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_LOCK_EXPIRED (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NO_SUCH_LOCK (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  digest_path_from_path (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ lock_expired (TYPE_1__*) ; 
 int /*<<< orphan*/  read_digest_file (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  unlock_single (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_lock(svn_lock_t **lock_p,
         svn_fs_t *fs,
         const char *path,
         svn_boolean_t have_write_lock,
         svn_boolean_t must_exist,
         apr_pool_t *pool)
{
  svn_lock_t *lock = NULL;
  const char *digest_path;
  svn_node_kind_t kind;

  SVN_ERR(digest_path_from_path(&digest_path, fs->path, path, pool));
  SVN_ERR(svn_io_check_path(digest_path, &kind, pool));

  *lock_p = NULL;
  if (kind != svn_node_none)
    SVN_ERR(read_digest_file(NULL, &lock, fs->path, digest_path, pool));

  if (! lock)
    return must_exist ? SVN_FS__ERR_NO_SUCH_LOCK(fs, path) : SVN_NO_ERROR;

  /* Don't return an expired lock. */
  if (lock_expired(lock))
    {
      /* Only remove the lock if we have the write lock.
         Read operations shouldn't change the filesystem. */
      if (have_write_lock)
        SVN_ERR(unlock_single(fs, lock, pool));
      return SVN_FS__ERR_LOCK_EXPIRED(fs, lock->token);
    }

  *lock_p = lock;
  return SVN_NO_ERROR;
}