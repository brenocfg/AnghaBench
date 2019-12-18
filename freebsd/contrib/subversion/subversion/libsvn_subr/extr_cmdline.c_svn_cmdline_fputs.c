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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_PIPE_WRITE_ERROR ; 
 int /*<<< orphan*/  SVN_ERR_IO_WRITE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_EPIPE (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ _cputws (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_get_os_error () ; 
 scalar_t__ errno ; 
 scalar_t__ fputs (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ shortcut_stderr_to_console ; 
 scalar_t__ shortcut_stdout_to_console ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/ * svn_cmdline_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_cmdline_cstring_from_utf8_fuzzy (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_utf__win32_utf8_to_utf16 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline_fputs(const char *string, FILE* stream, apr_pool_t *pool)
{
  svn_error_t *err;
  const char *out;

#ifdef USE_WIN32_CONSOLE_SHORTCUT
  /* For legacy reasons the Visual C++ runtime converts output to the console
     from the native 'ansi' encoding, to unicode, then back to 'ansi' and then
     onwards to the console which is implemented as unicode.

     For operations like 'svn status -v' this may cause about 70% of the total
     processing time, with absolutely no gain.

     For this specific scenario this shortcut exists. It has the nice side
     effect of allowing full unicode output to the console.

     Note that this shortcut is not used when the output is redirected, as in
     that case the data is put on the pipe/file after the first conversion to
     ansi. In this case the most expensive conversion is already avoided.
   */
  if ((stream == stdout && shortcut_stdout_to_console)
      || (stream == stderr && shortcut_stderr_to_console))
    {
      WCHAR *result;

      if (string[0] == '\0')
        return SVN_NO_ERROR;

      SVN_ERR(svn_cmdline_fflush(stream)); /* Flush existing output */

      SVN_ERR(svn_utf__win32_utf8_to_utf16(&result, string, NULL, pool));

      if (_cputws(result))
        {
          if (apr_get_os_error())
          {
            return svn_error_wrap_apr(apr_get_os_error(), _("Write error"));
          }
        }

      return SVN_NO_ERROR;
    }
#endif

  err = svn_cmdline_cstring_from_utf8(&out, string, pool);

  if (err)
    {
      svn_error_clear(err);
      out = svn_cmdline_cstring_from_utf8_fuzzy(string, pool);
    }

  /* On POSIX systems, errno will be set on an error in fputs, but this might
     not be the case on other platforms.  We reset errno and only
     use it if it was set by the below fputs call.  Else, we just return
     a generic error. */
  errno = 0;

  if (fputs(out, stream) == EOF)
    {
      if (apr_get_os_error()) /* is errno on POSIX */
        {
          /* ### Issue #3014: Return a specific error for broken pipes,
           * ### with a single element in the error chain. */
          if (SVN__APR_STATUS_IS_EPIPE(apr_get_os_error()))
            return svn_error_create(SVN_ERR_IO_PIPE_WRITE_ERROR, NULL, NULL);
          else
            return svn_error_wrap_apr(apr_get_os_error(), _("Write error"));
        }
      else
        return svn_error_create(SVN_ERR_IO_WRITE_ERROR, NULL, NULL);
    }

  return SVN_NO_ERROR;
}