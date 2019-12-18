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
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct svnadmin_opt_state {int /*<<< orphan*/  repository_path; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_FS_UNSUPPORTED_UPGRADE ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_LOCKED ; 
 scalar_t__ SVN_ERR_REPOS_UNSUPPORTED_UPGRADE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repos_notify_handler ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  svn_cmdline__disable_cancellation_handler () ; 
 TYPE_1__* svn_cmdline_fflush (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_quick_wrap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_repos_upgrade2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream_for_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
subcommand_upgrade(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  svn_error_t *err;
  struct svnadmin_opt_state *opt_state = baton;
  svn_stream_t *feedback_stream = NULL;

  /* Expect no more arguments. */
  SVN_ERR(parse_args(NULL, os, 0, 0, pool));

  SVN_ERR(svn_stream_for_stdout(&feedback_stream, pool));

  /* Restore default signal handlers. */
  svn_cmdline__disable_cancellation_handler();

  err = svn_repos_upgrade2(opt_state->repository_path, TRUE,
                           repos_notify_handler, feedback_stream, pool);
  if (err)
    {
      if (APR_STATUS_IS_EAGAIN(err->apr_err))
        {
          svn_error_clear(err);
          err = SVN_NO_ERROR;
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
          SVN_ERR(svn_repos_upgrade2(opt_state->repository_path, FALSE,
                                     repos_notify_handler, feedback_stream,
                                     pool));
        }
      else if (err->apr_err == SVN_ERR_FS_UNSUPPORTED_UPGRADE)
        {
          return svn_error_quick_wrap(err,
                    _("Upgrade of this repository's underlying versioned "
                    "filesystem is not supported; consider "
                    "dumping and loading the data elsewhere"));
        }
      else if (err->apr_err == SVN_ERR_REPOS_UNSUPPORTED_UPGRADE)
        {
          return svn_error_quick_wrap(err,
                    _("Upgrade of this repository is not supported; consider "
                    "dumping and loading the data elsewhere"));
        }
    }
  SVN_ERR(err);

  SVN_ERR(svn_cmdline_printf(pool, _("\nUpgrade completed.\n")));
  return SVN_NO_ERROR;
}