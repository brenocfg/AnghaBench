#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  out; int /*<<< orphan*/  err; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_WRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/  SVN_NULL_DEVICE_NAME ; 
 char const* SVN_REPOS__HOOKS_ENV_DEFAULT_SECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * check_hook_result (char const*,char const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_from_env_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_io_start_cmd3 (TYPE_1__*,char*,char const*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_from_aprfile (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_hook_cmd(svn_string_t **result,
             const char *name,
             const char *cmd,
             const char **args,
             apr_hash_t *hooks_env,
             apr_file_t *stdin_handle,
             apr_pool_t *pool)
{
  apr_file_t *null_handle;
  apr_status_t apr_err;
  svn_error_t *err;
  apr_proc_t cmd_proc = {0};
  apr_pool_t *cmd_pool;
  apr_hash_t *hook_env = NULL;

  if (result)
    {
      null_handle = NULL;
    }
  else
    {
      /* Redirect stdout to the null device */
        apr_err = apr_file_open(&null_handle, SVN_NULL_DEVICE_NAME, APR_WRITE,
                                APR_OS_DEFAULT, pool);
        if (apr_err)
          return svn_error_wrap_apr
            (apr_err, _("Can't create null stdout for hook '%s'"), cmd);
    }

  /* Tie resources allocated for the command to a special pool which we can
   * destroy in order to clean up the stderr pipe opened for the process. */
  cmd_pool = svn_pool_create(pool);

  /* Check if a custom environment is defined for this hook, or else
   * whether a default environment is defined. */
  if (hooks_env)
    {
      hook_env = svn_hash_gets(hooks_env, name);
      if (hook_env == NULL)
        hook_env = svn_hash_gets(hooks_env,
                                 SVN_REPOS__HOOKS_ENV_DEFAULT_SECTION);
    }

  err = svn_io_start_cmd3(&cmd_proc, ".", cmd, args,
                          env_from_env_hash(hook_env, pool, pool),
                          FALSE, FALSE, stdin_handle, result != NULL,
                          null_handle, TRUE, NULL, cmd_pool);
  if (!err)
    err = check_hook_result(name, cmd, &cmd_proc, cmd_proc.err, pool);
  else
    {
      /* The command could not be started for some reason. */
      err = svn_error_createf(SVN_ERR_REPOS_BAD_ARGS, err,
                              _("Failed to start '%s' hook"), cmd);
    }

  /* Hooks are fallible, and so hook failure is "expected" to occur at
     times.  When such a failure happens we still want to close the pipe
     and null file */
  if (!err && result)
    {
      svn_stringbuf_t *native_stdout;
      err = svn_stringbuf_from_aprfile(&native_stdout, cmd_proc.out, pool);
      if (!err)
        *result = svn_stringbuf__morph_into_string(native_stdout);
    }

  /* Close resources allocated by svn_io_start_cmd3(), such as the pipe. */
  svn_pool_destroy(cmd_pool);

  /* Close the null handle. */
  if (null_handle)
    {
      apr_err = apr_file_close(null_handle);
      if (!err && apr_err)
        return svn_error_wrap_apr(apr_err, _("Error closing null file"));
    }

  return svn_error_trace(err);
}