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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  char* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (char*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/ * svn_cl__time_cstring_to_human_cstring (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cmdline_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static svn_error_t *
print_line_info(svn_stream_t *out,
                svn_revnum_t revision,
                const char *author,
                const char *date,
                const char *path,
                svn_boolean_t verbose,
                int rev_maxlength,
                apr_pool_t *pool)
{
  const char *time_utf8;
  const char *time_stdout;
  const char *rev_str;

  rev_str = SVN_IS_VALID_REVNUM(revision)
    ? apr_psprintf(pool, "%*ld", rev_maxlength, revision)
    : apr_psprintf(pool, "%*s", rev_maxlength, "-");

  if (verbose)
    {
      if (date)
        {
          SVN_ERR(svn_cl__time_cstring_to_human_cstring(&time_utf8,
                                                        date, pool));
          SVN_ERR(svn_cmdline_cstring_from_utf8(&time_stdout, time_utf8,
                                                pool));
        }
      else
        {
          /* ### This is a 44 characters long string. It assumes the current
             format of svn_time_to_human_cstring and also 3 letter
             abbreviations for the month and weekday names.  Else, the
             line contents will be misaligned. */
          time_stdout = "                                           -";
        }

      SVN_ERR(svn_stream_printf(out, pool, "%s %10s %s ", rev_str,
                                author ? author : "         -",
                                time_stdout));

      if (path)
        SVN_ERR(svn_stream_printf(out, pool, "%-14s ", path));
    }
  else
    {
      return svn_stream_printf(out, pool, "%s %10.10s ", rev_str,
                               author ? author : "         -");
    }

  return SVN_NO_ERROR;
}