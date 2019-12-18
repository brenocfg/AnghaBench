#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {TYPE_10__* fs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_41__ {void* token; int /*<<< orphan*/  expiration_date; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  is_dav_comment; void* comment; void* owner; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ svn_lock_t ;
struct TYPE_42__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
struct lock_args {scalar_t__ current_rev; TYPE_3__** lock_p; int /*<<< orphan*/  path; int /*<<< orphan*/  expiration_date; int /*<<< orphan*/  is_dav_comment; scalar_t__ comment; int /*<<< orphan*/  result_pool; scalar_t__ token; int /*<<< orphan*/  steal_lock; } ;
struct TYPE_39__ {scalar_t__ username; } ;
struct TYPE_38__ {TYPE_1__* access_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 scalar_t__ SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 scalar_t__ SVN_ERR_FS_LOCK_EXPIRED ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_FS_OUT_OF_DATE ; 
 TYPE_4__* SVN_FS__ERR_NOT_FILE (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* SVN_FS__ERR_NO_USER (TYPE_10__*) ; 
 TYPE_4__* SVN_FS__ERR_PATH_ALREADY_LOCKED (TYPE_10__*,TYPE_3__*) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_4__* SVN_NO_ERROR ; 
 char* _ (char*) ; 
 TYPE_4__* add_lock_and_token (TYPE_3__*,void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  apr_time_now () ; 
 TYPE_4__* delete_lock_and_token (void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_create (scalar_t__,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_fs_base__generate_lock_token (void**,TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_fs_base__get_lock_helper (TYPE_3__**,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_fs_base__get_path_created_rev (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_fs_base__get_path_kind (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_fs_bdb__lock_get (TYPE_3__**,TYPE_10__*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_lock_create (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 

__attribute__((used)) static svn_error_t *
txn_body_lock(void *baton, trail_t *trail)
{
  struct lock_args *args = baton;
  svn_node_kind_t kind = svn_node_file;
  svn_lock_t *existing_lock;
  svn_lock_t *lock;

  *args->lock_p = NULL;

  SVN_ERR(svn_fs_base__get_path_kind(&kind, args->path, trail, trail->pool));

  /* Until we implement directory locks someday, we only allow locks
     on files. */
  if (kind == svn_node_dir)
    return SVN_FS__ERR_NOT_FILE(trail->fs, args->path);

  /* While our locking implementation easily supports the locking of
     nonexistent paths, we deliberately choose not to allow such madness. */
  if (kind == svn_node_none)
    {
      if (SVN_IS_VALID_REVNUM(args->current_rev))
        return svn_error_createf(
          SVN_ERR_FS_OUT_OF_DATE, NULL,
          _("Path '%s' doesn't exist in HEAD revision"),
          args->path);
      else
        return svn_error_createf(
          SVN_ERR_FS_NOT_FOUND, NULL,
          _("Path '%s' doesn't exist in HEAD revision"),
          args->path);
    }

  /* There better be a username attached to the fs. */
  if (!trail->fs->access_ctx || !trail->fs->access_ctx->username)
    return SVN_FS__ERR_NO_USER(trail->fs);

  /* Is the caller attempting to lock an out-of-date working file? */
  if (SVN_IS_VALID_REVNUM(args->current_rev))
    {
      svn_revnum_t created_rev;
      SVN_ERR(svn_fs_base__get_path_created_rev(&created_rev, args->path,
                                                trail, trail->pool));

      /* SVN_INVALID_REVNUM means the path doesn't exist.  So
         apparently somebody is trying to lock something in their
         working copy, but somebody else has deleted the thing
         from HEAD.  That counts as being 'out of date'. */
      if (! SVN_IS_VALID_REVNUM(created_rev))
        return svn_error_createf(SVN_ERR_FS_OUT_OF_DATE, NULL,
                                 "Path '%s' doesn't exist in HEAD revision",
                                 args->path);

      if (args->current_rev < created_rev)
        return svn_error_createf(SVN_ERR_FS_OUT_OF_DATE, NULL,
                                 "Lock failed: newer version of '%s' exists",
                                 args->path);
    }

  /* If the caller provided a TOKEN, we *really* need to see
     if a lock already exists with that token, and if so, verify that
     the lock's path matches PATH.  Otherwise we run the risk of
     breaking the 1-to-1 mapping of lock tokens to locked paths. */
  if (args->token)
    {
      svn_lock_t *lock_from_token;
      svn_error_t *err = svn_fs_bdb__lock_get(&lock_from_token, trail->fs,
                                              args->token, trail,
                                              trail->pool);
      if (err && ((err->apr_err == SVN_ERR_FS_LOCK_EXPIRED)
                  || (err->apr_err == SVN_ERR_FS_BAD_LOCK_TOKEN)))
        {
          svn_error_clear(err);
        }
      else
        {
          SVN_ERR(err);
          if (strcmp(lock_from_token->path, args->path) != 0)
            return svn_error_create(SVN_ERR_FS_BAD_LOCK_TOKEN, NULL,
                                    "Lock failed: token refers to existing "
                                    "lock with non-matching path.");
        }
    }

  /* Is the path already locked?

     Note that this next function call will automatically ignore any
     errors about {the path not existing as a key, the path's token
     not existing as a key, the lock just having been expired}.  And
     that's totally fine.  Any of these three errors are perfectly
     acceptable to ignore; it means that the path is now free and
     clear for locking, because the bdb funcs just cleared out both
     of the tables for us.   */
  SVN_ERR(svn_fs_base__get_lock_helper(&existing_lock, args->path,
                                       trail, trail->pool));
  if (existing_lock)
    {
      if (! args->steal_lock)
        {
          /* Sorry, the path is already locked. */
          return SVN_FS__ERR_PATH_ALREADY_LOCKED(trail->fs,
                                                 existing_lock);
        }
      else
        {
          /* ARGS->steal_lock is set, so fs_username is "stealing" the
             lock from lock->owner.  Destroy the existing lock. */
          SVN_ERR(delete_lock_and_token(existing_lock->token,
                                        existing_lock->path, trail));
        }
    }

  /* Create a new lock, and add it to the tables. */
  lock = svn_lock_create(args->result_pool);
  if (args->token)
    lock->token = apr_pstrdup(args->result_pool, args->token);
  else
    SVN_ERR(svn_fs_base__generate_lock_token(&(lock->token), trail->fs,
                                             args->result_pool));
  lock->path = args->path; /* Already in result_pool. */
  lock->owner = apr_pstrdup(args->result_pool, trail->fs->access_ctx->username);
  lock->comment = apr_pstrdup(args->result_pool, args->comment);
  lock->is_dav_comment = args->is_dav_comment;
  lock->creation_date = apr_time_now();
  lock->expiration_date = args->expiration_date;
  SVN_ERR(add_lock_and_token(lock, lock->token, args->path, trail));
  *(args->lock_p) = lock;

  return SVN_NO_ERROR;
}