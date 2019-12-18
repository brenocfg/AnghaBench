#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* fs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
struct TYPE_17__ {int /*<<< orphan*/ * owner; } ;
typedef  TYPE_3__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct unlock_args {int /*<<< orphan*/  path; int /*<<< orphan*/ * token; int /*<<< orphan*/  break_lock; } ;
struct TYPE_18__ {TYPE_1__* access_ctx; } ;
struct TYPE_15__ {char const* username; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_LOCK_OWNER_MISMATCH (TYPE_5__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NO_SUCH_LOCK (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NO_USER (TYPE_5__*) ; 
 int /*<<< orphan*/ * delete_lock_and_token (char const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__err_no_lock_token (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__lock_get (TYPE_3__**,TYPE_5__*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__lock_token_get (char const**,TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_unlock(void *baton, trail_t *trail)
{
  struct unlock_args *args = baton;
  const char *lock_token;
  svn_lock_t *lock;

  /* This could return SVN_ERR_FS_BAD_LOCK_TOKEN or SVN_ERR_FS_LOCK_EXPIRED. */
  SVN_ERR(svn_fs_bdb__lock_token_get(&lock_token, trail->fs, args->path,
                                     trail, trail->pool));

  /* If not breaking the lock, we need to do some more checking. */
  if (!args->break_lock)
    {
      /* Sanity check: The lock token must exist, and must match. */
      if (args->token == NULL)
        return svn_fs_base__err_no_lock_token(trail->fs, args->path);
      else if (strcmp(lock_token, args->token) != 0)
        return SVN_FS__ERR_NO_SUCH_LOCK(trail->fs, args->path);

      SVN_ERR(svn_fs_bdb__lock_get(&lock, trail->fs, lock_token,
                                   trail, trail->pool));

      /* There better be a username attached to the fs. */
      if (!trail->fs->access_ctx || !trail->fs->access_ctx->username)
        return SVN_FS__ERR_NO_USER(trail->fs);

      /* And that username better be the same as the lock's owner. */
      if (strcmp(trail->fs->access_ctx->username, lock->owner) != 0)
        return SVN_FS__ERR_LOCK_OWNER_MISMATCH(
           trail->fs,
           trail->fs->access_ctx->username,
           lock->owner);
    }

  /* Remove a row from each of the locking tables. */
  return delete_lock_and_token(lock_token, args->path, trail);
}