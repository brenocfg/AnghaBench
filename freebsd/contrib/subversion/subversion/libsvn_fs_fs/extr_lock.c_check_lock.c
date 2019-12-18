#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_3__ {scalar_t__ current_rev; } ;
typedef  TYPE_1__ svn_fs_lock_target_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct lock_baton {int /*<<< orphan*/  fs; int /*<<< orphan*/  steal_lock; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_FS_OUT_OF_DATE ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NOT_FILE (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_PATH_ALREADY_LOCKED (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_lock_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_fs__check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__node_created_rev (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 

__attribute__((used)) static svn_error_t *
check_lock(svn_error_t **fs_err,
           const char *path,
           const svn_fs_lock_target_t *target,
           struct lock_baton *lb,
           svn_fs_root_t *root,
           svn_revnum_t youngest_rev,
           apr_pool_t *pool)
{
  svn_node_kind_t kind;
  svn_lock_t *existing_lock;

  *fs_err = SVN_NO_ERROR;

  SVN_ERR(svn_fs_fs__check_path(&kind, root, path, pool));
  if (kind == svn_node_dir)
    {
      *fs_err = SVN_FS__ERR_NOT_FILE(lb->fs, path);
      return SVN_NO_ERROR;
    }

  /* While our locking implementation easily supports the locking of
     nonexistent paths, we deliberately choose not to allow such madness. */
  if (kind == svn_node_none)
    {
      if (SVN_IS_VALID_REVNUM(target->current_rev))
        *fs_err = svn_error_createf(
          SVN_ERR_FS_OUT_OF_DATE, NULL,
          _("Path '%s' doesn't exist in HEAD revision"),
          path);
      else
        *fs_err = svn_error_createf(
          SVN_ERR_FS_NOT_FOUND, NULL,
          _("Path '%s' doesn't exist in HEAD revision"),
          path);

      return SVN_NO_ERROR;
    }

  /* Is the caller attempting to lock an out-of-date working file? */
  if (SVN_IS_VALID_REVNUM(target->current_rev))
    {
      svn_revnum_t created_rev;

      if (target->current_rev > youngest_rev)
        {
          *fs_err = svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                                      _("No such revision %ld"),
                                      target->current_rev);
          return SVN_NO_ERROR;
        }

      SVN_ERR(svn_fs_fs__node_created_rev(&created_rev, root, path,
                                          pool));

      /* SVN_INVALID_REVNUM means the path doesn't exist.  So
         apparently somebody is trying to lock something in their
         working copy, but somebody else has deleted the thing
         from HEAD.  That counts as being 'out of date'. */
      if (! SVN_IS_VALID_REVNUM(created_rev))
        {
          *fs_err = svn_error_createf
            (SVN_ERR_FS_OUT_OF_DATE, NULL,
             _("Path '%s' doesn't exist in HEAD revision"), path);

          return SVN_NO_ERROR;
        }

      if (target->current_rev < created_rev)
        {
          *fs_err = svn_error_createf
            (SVN_ERR_FS_OUT_OF_DATE, NULL,
             _("Lock failed: newer version of '%s' exists"), path);

          return SVN_NO_ERROR;
        }
    }

  /* If the caller provided a TOKEN, we *really* need to see
     if a lock already exists with that token, and if so, verify that
     the lock's path matches PATH.  Otherwise we run the risk of
     breaking the 1-to-1 mapping of lock tokens to locked paths. */
  /* ### TODO:  actually do this check.  This is tough, because the
     schema doesn't supply a lookup-by-token mechanism. */

  /* Is the path already locked?

     Note that this next function call will automatically ignore any
     errors about {the path not existing as a key, the path's token
     not existing as a key, the lock just having been expired}.  And
     that's totally fine.  Any of these three errors are perfectly
     acceptable to ignore; it means that the path is now free and
     clear for locking, because the fsfs funcs just cleared out both
     of the tables for us.   */
  SVN_ERR(get_lock_helper(lb->fs, &existing_lock, path, TRUE, pool));
  if (existing_lock)
    {
      if (! lb->steal_lock)
        {
          /* Sorry, the path is already locked. */
          *fs_err = SVN_FS__ERR_PATH_ALREADY_LOCKED(lb->fs, existing_lock);
          return SVN_NO_ERROR;
        }
    }

  return SVN_NO_ERROR;
}