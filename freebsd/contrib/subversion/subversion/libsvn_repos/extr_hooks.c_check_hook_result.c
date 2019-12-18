#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  char const* apr_exit_why_e ;

/* Variables and functions */
 scalar_t__ APR_PROC_CHECK_EXIT (char const*) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_HOOK_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* _ (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_wait_for_cmd (int /*<<< orphan*/ *,char const*,int*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char const*) ; 
 TYPE_1__* svn_stringbuf_createf (int /*<<< orphan*/ *,char const*,char const*,...) ; 
 int /*<<< orphan*/ * svn_stringbuf_from_aprfile (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_utf_cstring_to_utf8 (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_hook_result(const char *name, const char *cmd, apr_proc_t *cmd_proc,
                  apr_file_t *read_errhandle, apr_pool_t *pool)
{
  svn_error_t *err, *err2;
  svn_stringbuf_t *native_stderr, *failure_message;
  const char *utf8_stderr;
  int exitcode;
  apr_exit_why_e exitwhy;

  err2 = svn_stringbuf_from_aprfile(&native_stderr, read_errhandle, pool);

  err = svn_io_wait_for_cmd(cmd_proc, cmd, &exitcode, &exitwhy, pool);
  if (err)
    {
      svn_error_clear(err2);
      return svn_error_trace(err);
    }

  if (APR_PROC_CHECK_EXIT(exitwhy) && exitcode == 0)
    {
      /* The hook exited cleanly.  However, if we got an error reading
         the hook's stderr, fail the hook anyway, because this might be
         symptomatic of a more important problem. */
      if (err2)
        {
          return svn_error_createf
            (SVN_ERR_REPOS_HOOK_FAILURE, err2,
             _("'%s' hook succeeded, but error output could not be read"),
             name);
        }

      return SVN_NO_ERROR;
    }

  /* The hook script failed. */

  /* If we got the stderr output okay, try to translate it into UTF-8.
     Ensure there is something sensible in the UTF-8 string regardless. */
  if (!err2)
    {
      err2 = svn_utf_cstring_to_utf8(&utf8_stderr, native_stderr->data, pool);
      if (err2)
        utf8_stderr = _("[Error output could not be translated from the "
                        "native locale to UTF-8.]");
    }
  else
    {
      utf8_stderr = _("[Error output could not be read.]");
    }
  /*### It would be nice to include the text of any translation or read
        error in the messages above before we clear it here. */
  svn_error_clear(err2);

  if (!APR_PROC_CHECK_EXIT(exitwhy))
    {
      failure_message = svn_stringbuf_createf(pool,
        _("'%s' hook failed (did not exit cleanly: "
          "apr_exit_why_e was %d, exitcode was %d).  "),
        name, exitwhy, exitcode);
    }
  else
    {
      const char *action;
      if (strcmp(name, "start-commit") == 0
          || strcmp(name, "pre-commit") == 0)
        action = _("Commit");
      else if (strcmp(name, "pre-revprop-change") == 0)
        action = _("Revprop change");
      else if (strcmp(name, "pre-lock") == 0)
        action = _("Lock");
      else if (strcmp(name, "pre-unlock") == 0)
        action = _("Unlock");
      else
        action = NULL;
      if (action == NULL)
        failure_message = svn_stringbuf_createf(
            pool, _("%s hook failed (exit code %d)"),
            name, exitcode);
      else
        failure_message = svn_stringbuf_createf(
            pool, _("%s blocked by %s hook (exit code %d)"),
            action, name, exitcode);
    }

  if (utf8_stderr[0])
    {
      svn_stringbuf_appendcstr(failure_message,
                               _(" with output:\n"));
      svn_stringbuf_appendcstr(failure_message, utf8_stderr);
    }
  else
    {
      svn_stringbuf_appendcstr(failure_message,
                               _(" with no output."));
    }

  return svn_error_create(SVN_ERR_REPOS_HOOK_FAILURE, err,
                          failure_message->data);
}