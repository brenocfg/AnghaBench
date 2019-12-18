#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* fs; int /*<<< orphan*/  break_lock; } ;
typedef  TYPE_2__ unlock_baton_t ;
struct TYPE_11__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_3__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {TYPE_1__* access_ctx; } ;
struct TYPE_9__ {char const* username; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_FS__ERR_LOCK_OWNER_MISMATCH (TYPE_5__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NO_SUCH_LOCK (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_lock (TYPE_3__**,TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
check_unlock(svn_error_t **fs_err,
             const char *path,
             const char *token,
             unlock_baton_t *ub,
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