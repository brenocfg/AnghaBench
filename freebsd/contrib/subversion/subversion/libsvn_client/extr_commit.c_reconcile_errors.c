#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BASE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_quick_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
reconcile_errors(svn_error_t *commit_err,
                 svn_error_t *unlock_err,
                 svn_error_t *bump_err,
                 apr_pool_t *pool)
{
  svn_error_t *err;

  /* Early release (for good behavior). */
  if (! (commit_err || unlock_err || bump_err))
    return SVN_NO_ERROR;

  /* If there was a commit error, start off our error chain with
     that. */
  if (commit_err)
    {
      commit_err = svn_error_quick_wrap
        (commit_err, _("Commit failed (details follow):"));
      err = commit_err;
    }

  /* Else, create a new "general" error that will lead off the errors
     that follow. */
  else
    err = svn_error_create(SVN_ERR_BASE, NULL,
                           _("Commit succeeded, but other errors follow:"));

  /* If there was an unlock error... */
  if (unlock_err)
    {
      /* Wrap the error with some headers. */
      unlock_err = svn_error_quick_wrap
        (unlock_err, _("Error unlocking locked dirs (details follow):"));

      /* Append this error to the chain. */
      svn_error_compose(err, unlock_err);
    }

  /* If there was a bumping error... */
  if (bump_err)
    {
      /* Wrap the error with some headers. */
      bump_err = svn_error_quick_wrap
        (bump_err, _("Error bumping revisions post-commit (details follow):"));

      /* Append this error to the chain. */
      svn_error_compose(err, bump_err);
    }

  return err;
}