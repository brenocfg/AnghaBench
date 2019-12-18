#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct svnadmin_opt_state {int /*<<< orphan*/  repository_path; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_LOCKED ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_cancel ; 
 TYPE_1__* open_repos (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct svnadmin_opt_state*,int /*<<< orphan*/ *) ; 
 TYPE_1__* parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repos_notify_handler ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  svn_cmdline__disable_cancellation_handler () ; 
 TYPE_1__* svn_cmdline_fflush (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_repos_recover4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream_for_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
subcommand_recover(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  svn_revnum_t youngest_rev;
  svn_repos_t *repos;
  svn_error_t *err;
  struct svnadmin_opt_state *opt_state = baton;
  svn_stream_t *feedback_stream = NULL;

  /* Expect no more arguments. */
  SVN_ERR(parse_args(NULL, os, 0, 0, pool));

  SVN_ERR(svn_stream_for_stdout(&feedback_stream, pool));

  /* Restore default signal handlers until after we have acquired the
   * exclusive lock so that the user interrupt before we actually
   * touch the repository. */
  svn_cmdline__disable_cancellation_handler();

  err = svn_repos_recover4(opt_state->repository_path, TRUE,
                           repos_notify_handler, feedback_stream,
                           check_cancel, NULL, pool);
  if (err)
    {
      if (! APR_STATUS_IS_EAGAIN(err->apr_err))
        return err;
      svn_error_clear(err);
      if (! opt_state->wait)
        return svn_error_create(SVN_ERR_REPOS_LOCKED, NULL,
                                _("Failed to get exclusive repository "
                                  "access; perhaps another process\n"
                                  "such as httpd, svnserve or svn "
                                  "has it open?"));
      SVN_ERR(svn_cmdline_printf(pool,
                                 _("Waiting on repository lock; perhaps"
                                   " another process has it open?\n")));
      SVN_ERR(svn_cmdline_fflush(stdout));
      SVN_ERR(svn_repos_recover4(opt_state->repository_path, FALSE,
                                 repos_notify_handler, feedback_stream,
                                 check_cancel, NULL, pool));
    }

  SVN_ERR(svn_cmdline_printf(pool, _("\nRecovery completed.\n")));

  /* Since db transactions may have been replayed, it's nice to tell
     people what the latest revision is.  It also proves that the
     recovery actually worked. */
  SVN_ERR(open_repos(&repos, opt_state->repository_path, opt_state, pool));
  SVN_ERR(svn_fs_youngest_rev(&youngest_rev, svn_repos_fs(repos), pool));
  SVN_ERR(svn_cmdline_printf(pool, _("The latest repos revision is %ld.\n"),
                             youngest_rev));

  return SVN_NO_ERROR;
}