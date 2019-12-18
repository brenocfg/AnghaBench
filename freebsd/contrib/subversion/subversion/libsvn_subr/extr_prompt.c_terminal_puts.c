#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  outfd; } ;
typedef  TYPE_1__ terminal_handle_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _cputs (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * svn_cmdline_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_cmdline_cstring_from_utf8_fuzzy (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
terminal_puts(const char *string, terminal_handle_t *terminal,
              apr_pool_t *pool)
{
  svn_error_t *err;
  const char *converted;

  err = svn_cmdline_cstring_from_utf8(&converted, string, pool);
  if (err)
    {
      svn_error_clear(err);
      converted = svn_cmdline_cstring_from_utf8_fuzzy(string, pool);
    }

#ifdef WIN32
  if (!terminal->outfd)
    {
      /* See terminal_open; we're using Console I/O. */
      _cputs(converted);
      return SVN_NO_ERROR;
    }
#endif

  SVN_ERR(svn_io_file_write_full(terminal->outfd, converted,
                                 strlen(converted), NULL, pool));

  return svn_error_trace(svn_io_file_flush(terminal->outfd, pool));
}