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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_exit_why_e ;

/* Variables and functions */
 scalar_t__ APR_PROC_CHECK_CORE_DUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_PROC_CHECK_EXIT (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_PROC_CHECK_SIGNALED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_PROC_EXIT ; 
 int /*<<< orphan*/  APR_STATUS_IS_CHILD_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_WAIT ; 
 int /*<<< orphan*/  SVN_ERR_EXTERNAL_PROGRAM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_proc_wait (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,...) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

svn_error_t *
svn_io_wait_for_cmd(apr_proc_t *cmd_proc,
                    const char *cmd,
                    int *exitcode,
                    apr_exit_why_e *exitwhy,
                    apr_pool_t *pool)
{
  apr_status_t apr_err;
  apr_exit_why_e exitwhy_val;
  int exitcode_val;

  /* The Win32 apr_proc_wait doesn't set this... */
  exitwhy_val = APR_PROC_EXIT;

  /* Wait for the cmd command to finish. */
  apr_err = apr_proc_wait(cmd_proc, &exitcode_val, &exitwhy_val, APR_WAIT);
  if (!APR_STATUS_IS_CHILD_DONE(apr_err))
    return svn_error_wrap_apr(apr_err, _("Error waiting for process '%s'"),
                              cmd);

  if (exitwhy)
    *exitwhy = exitwhy_val;
  else if (APR_PROC_CHECK_SIGNALED(exitwhy_val)
           && APR_PROC_CHECK_CORE_DUMP(exitwhy_val))
    return svn_error_createf
      (SVN_ERR_EXTERNAL_PROGRAM, NULL,
       _("Process '%s' failed (signal %d, core dumped)"),
       cmd, exitcode_val);
  else if (APR_PROC_CHECK_SIGNALED(exitwhy_val))
    return svn_error_createf
      (SVN_ERR_EXTERNAL_PROGRAM, NULL,
       _("Process '%s' failed (signal %d)"),
       cmd, exitcode_val);
  else if (! APR_PROC_CHECK_EXIT(exitwhy_val))
    /* Don't really know what happened here. */
    return svn_error_createf
      (SVN_ERR_EXTERNAL_PROGRAM, NULL,
       _("Process '%s' failed (exitwhy %d, exitcode %d)"),
       cmd, exitwhy_val, exitcode_val);

  if (exitcode)
    *exitcode = exitcode_val;
  else if (exitcode_val != 0)
    return svn_error_createf
      (SVN_ERR_EXTERNAL_PROGRAM, NULL,
       _("Process '%s' returned error exitcode %d"), cmd, exitcode_val);

  return SVN_NO_ERROR;
}