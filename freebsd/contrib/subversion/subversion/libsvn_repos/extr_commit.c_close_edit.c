#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {TYPE_1__* repos; int /*<<< orphan*/  commit_callback_baton; int /*<<< orphan*/  commit_callback; int /*<<< orphan*/ * txn; int /*<<< orphan*/  txn_aborted; int /*<<< orphan*/ * txn_root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  invoke_commit_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_abort_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_close_root (int /*<<< orphan*/ *) ; 
 char* svn_repos__post_commit_error_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs_commit_txn (char const**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;
  svn_revnum_t new_revision = SVN_INVALID_REVNUM;
  svn_error_t *err;
  const char *conflict;
  const char *post_commit_err = NULL;

  /* If no transaction has been created (ie. if open_root wasn't
     called before close_edit), abort the operation here with an
     error. */
  if (! eb->txn)
    return svn_error_create(SVN_ERR_REPOS_BAD_ARGS, NULL,
                            "No valid transaction supplied to close_edit");

  /* Commit. */
  err = svn_repos_fs_commit_txn(&conflict, eb->repos,
                                &new_revision, eb->txn, pool);

  if (SVN_IS_VALID_REVNUM(new_revision))
    {
      /* The actual commit succeeded, i.e. the transaction does no longer
         exist and we can't use txn_root for conflict resolution etc.

         Since close_edit is supposed to release resources, do it now. */
      if (eb->txn_root)
        svn_fs_close_root(eb->txn_root);

      if (err)
        {
          /* If the error was in post-commit, then the commit itself
             succeeded.  In which case, save the post-commit warning
             (to be reported back to the client, who will probably
             display it as a warning) and clear the error. */
          post_commit_err = svn_repos__post_commit_error_str(err, pool);
          svn_error_clear(err);
        }

      /* Make sure a future abort doesn't perform
         any work. This may occur if the commit
         callback returns an error! */

      eb->txn = NULL;
      eb->txn_root = NULL;
    }
  else
    {
      /* ### todo: we should check whether it really was a conflict,
         and return the conflict info if so? */

      /* If the commit failed, it's *probably* due to a conflict --
         that is, the txn being out-of-date.  The filesystem gives us
         the ability to continue diddling the transaction and try
         again; but let's face it: that's not how the cvs or svn works
         from a user interface standpoint.  Thus we don't make use of
         this fs feature (for now, at least.)

         So, in a nutshell: svn commits are an all-or-nothing deal.
         Each commit creates a new fs txn which either succeeds or is
         aborted completely.  No second chances;  the user simply
         needs to update and commit again  :) */

      eb->txn_aborted = TRUE;

      return svn_error_trace(
                svn_error_compose_create(err,
                                         svn_fs_abort_txn(eb->txn, pool)));
    }

  /* At this point, the post-commit error has been converted to a string.
     That information will be passed to a callback, if provided. If the
     callback invocation fails in some way, that failure is returned here.
     IOW, the post-commit error information is low priority compared to
     other gunk here.  */

  /* Pass new revision information to the caller's callback. */
  return svn_error_trace(invoke_commit_cb(eb->commit_callback,
                                          eb->commit_callback_baton,
                                          eb->repos->fs,
                                          new_revision,
                                          post_commit_err,
                                          pool));
}