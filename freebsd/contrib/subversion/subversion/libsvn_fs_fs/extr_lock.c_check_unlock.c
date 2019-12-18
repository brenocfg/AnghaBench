#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_2__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct unlock_baton {TYPE_4__* fs; int /*<<< orphan*/  break_lock; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {TYPE_1__* access_ctx; } ;
struct TYPE_7__ {char const* username; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_FS__ERR_LOCK_OWNER_MISMATCH (TYPE_4__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NO_SUCH_LOCK (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_lock (TYPE_2__**,TYPE_4__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
check_unlock(svn_error_t **fs_err,
             const char *path,
             const char *token,
             struct unlock_baton *ub,
             svn_fs_root_t *root,
             apr_pool_t *pool)
{
  svn_lock_t *lock;

  *fs_err = get_lock(&lock, ub->fs, path, TRUE, TRUE, pool);
  if (!*fs_err && !ub->break_lock)
    {
      if (strcmp(token, lock->token) != 0)
        *fs_err = SVN_FS__ERR_NO_SUCH_LOCK(ub->fs, path);
      else if (strcmp(ub->fs->access_ctx->username, lock->owner) != 0)
        *fs_err = SVN_FS__ERR_LOCK_OWNER_MISMATCH(ub->fs,
                                                  ub->fs->access_ctx->username,
                                                  lock->owner);
    }

  return SVN_NO_ERROR;
}