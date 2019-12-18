#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  token; int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ svn_lock_t ;
struct TYPE_8__ {TYPE_1__* access_ctx; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock_tokens; int /*<<< orphan*/  username; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 int /*<<< orphan*/  SVN_ERR_FS_LOCK_OWNER_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_USER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
verify_lock(svn_fs_t *fs,
            svn_lock_t *lock,
            apr_pool_t *pool)
{
  if ((! fs->access_ctx) || (! fs->access_ctx->username))
    return svn_error_createf
      (SVN_ERR_FS_NO_USER, NULL,
       _("Cannot verify lock on path '%s'; no username available"),
       lock->path);

  else if (strcmp(fs->access_ctx->username, lock->owner) != 0)
    return svn_error_createf
      (SVN_ERR_FS_LOCK_OWNER_MISMATCH, NULL,
       _("User '%s' does not own lock on path '%s' (currently locked by '%s')"),
       fs->access_ctx->username, lock->path, lock->owner);

  else if (svn_hash_gets(fs->access_ctx->lock_tokens, lock->token) == NULL)
    return svn_error_createf
      (SVN_ERR_FS_BAD_LOCK_TOKEN, NULL,
       _("Cannot verify lock on path '%s'; no matching lock-token available"),
       lock->path);

  return SVN_NO_ERROR;
}