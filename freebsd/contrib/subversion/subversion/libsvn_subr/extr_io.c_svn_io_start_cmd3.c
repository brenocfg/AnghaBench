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
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_procattr_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FULL_BLOCK ; 
 int /*<<< orphan*/  APR_NO_PIPE ; 
 int /*<<< orphan*/  APR_PROGRAM ; 
 int /*<<< orphan*/  APR_PROGRAM_PATH ; 
 int /*<<< orphan*/  ERRFILE_KEY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char** apr_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_pool_userdata_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_proc_create (int /*<<< orphan*/ *,char const*,char const**,char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_procattr_child_err_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_procattr_child_errfn_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_procattr_child_in_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_procattr_child_out_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_procattr_cmdtype_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_procattr_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_procattr_dir_set (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_procattr_io_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_child_process_error ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,char const*) ; 

svn_error_t *
svn_io_start_cmd3(apr_proc_t *cmd_proc,
                  const char *path,
                  const char *cmd,
                  const char *const *args,
                  const char *const *env,
                  svn_boolean_t inherit,
                  svn_boolean_t infile_pipe,
                  apr_file_t *infile,
                  svn_boolean_t outfile_pipe,
                  apr_file_t *outfile,
                  svn_boolean_t errfile_pipe,
                  apr_file_t *errfile,
                  apr_pool_t *pool)
{
  apr_status_t apr_err;
  apr_procattr_t *cmdproc_attr;
  int num_args;
  const char **args_native;
  const char *cmd_apr;

  SVN_ERR_ASSERT(!((infile != NULL) && infile_pipe));
  SVN_ERR_ASSERT(!((outfile != NULL) && outfile_pipe));
  SVN_ERR_ASSERT(!((errfile != NULL) && errfile_pipe));

  /* Create the process attributes. */
  apr_err = apr_procattr_create(&cmdproc_attr, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err,
                              _("Can't create process '%s' attributes"),
                              cmd);

  /* Make sure we invoke cmd directly, not through a shell. */
  apr_err = apr_procattr_cmdtype_set(cmdproc_attr,
                                     inherit ? APR_PROGRAM_PATH : APR_PROGRAM);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't set process '%s' cmdtype"),
                              cmd);

  /* Set the process's working directory. */
  if (path)
    {
      const char *path_apr;

      /* APR doesn't like our canonical path format for current directory */
      if (path[0] == '\0')
        path = ".";

      SVN_ERR(cstring_from_utf8(&path_apr, path, pool));
      apr_err = apr_procattr_dir_set(cmdproc_attr, path_apr);
      if (apr_err)
        return svn_error_wrap_apr(apr_err,
                                  _("Can't set process '%s' directory"),
                                  cmd);
    }

  /* Use requested inputs and outputs.

     ### Unfortunately each of these apr functions creates a pipe and then
     overwrites the pipe file descriptor with the descriptor we pass
     in. The pipes can then never be closed. This is an APR bug. */
  if (infile)
    {
      apr_err = apr_procattr_child_in_set(cmdproc_attr, infile, NULL);
      if (apr_err)
        return svn_error_wrap_apr(apr_err,
                                  _("Can't set process '%s' child input"),
                                  cmd);
    }
  if (outfile)
    {
      apr_err = apr_procattr_child_out_set(cmdproc_attr, outfile, NULL);
      if (apr_err)
        return svn_error_wrap_apr(apr_err,
                                  _("Can't set process '%s' child outfile"),
                                  cmd);
    }
  if (errfile)
    {
      apr_err = apr_procattr_child_err_set(cmdproc_attr, errfile, NULL);
      if (apr_err)
        return svn_error_wrap_apr(apr_err,
                                  _("Can't set process '%s' child errfile"),
                                  cmd);
    }

  /* Forward request for pipes to APR. */
  if (infile_pipe || outfile_pipe || errfile_pipe)
    {
      apr_err = apr_procattr_io_set(cmdproc_attr,
                                    infile_pipe ? APR_FULL_BLOCK : APR_NO_PIPE,
                                    outfile_pipe ? APR_FULL_BLOCK : APR_NO_PIPE,
                                    errfile_pipe ? APR_FULL_BLOCK : APR_NO_PIPE);

      if (apr_err)
        return svn_error_wrap_apr(apr_err,
                                  _("Can't set process '%s' stdio pipes"),
                                  cmd);
    }

  /* Have the child print any problems executing its program to errfile. */
  apr_err = apr_pool_userdata_set(errfile, ERRFILE_KEY, NULL, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err,
                              _("Can't set process '%s' child errfile for "
                                "error handler"),
                              cmd);
  apr_err = apr_procattr_child_errfn_set(cmdproc_attr,
                                         handle_child_process_error);
  if (apr_err)
    return svn_error_wrap_apr(apr_err,
                              _("Can't set process '%s' error handler"),
                              cmd);

  /* Convert cmd and args from UTF-8 */
  SVN_ERR(cstring_from_utf8(&cmd_apr, cmd, pool));
  for (num_args = 0; args[num_args]; num_args++)
    ;
  args_native = apr_palloc(pool, (num_args + 1) * sizeof(char *));
  args_native[num_args] = NULL;
  while (num_args--)
    {
      /* ### Well, it turns out that on APR on Windows expects all
             program args to be in UTF-8. Callers of svn_io_run_cmd
             should be aware of that. */
      SVN_ERR(cstring_from_utf8(&args_native[num_args],
                                args[num_args], pool));
    }


  /* Start the cmd command. */
  apr_err = apr_proc_create(cmd_proc, cmd_apr, args_native,
                            inherit ? NULL : env, cmdproc_attr, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't start process '%s'"), cmd);

  return SVN_NO_ERROR;
}