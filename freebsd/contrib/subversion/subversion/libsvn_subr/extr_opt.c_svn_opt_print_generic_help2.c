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
typedef  int /*<<< orphan*/  svn_opt_subcommand_desc2_t ;
struct TYPE_5__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_option_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_ERR_IO_PIPE_WRITE_ERROR ; 
 TYPE_1__* print_generic_help_body (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_handle_error2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
svn_opt_print_generic_help2(const char *header,
                            const svn_opt_subcommand_desc2_t *cmd_table,
                            const apr_getopt_option_t *opt_table,
                            const char *footer,
                            apr_pool_t *pool, FILE *stream)
{
  svn_error_t *err;

  err = print_generic_help_body(header, cmd_table, opt_table, footer, pool,
                                stream);

  /* Issue #3014:
   * Don't print anything on broken pipes. The pipe was likely
   * closed by the process at the other end. We expect that
   * process to perform error reporting as necessary.
   *
   * ### This assumes that there is only one error in a chain for
   * ### SVN_ERR_IO_PIPE_WRITE_ERROR. See svn_cmdline_fputs(). */
  if (err && err->apr_err != SVN_ERR_IO_PIPE_WRITE_ERROR)
    svn_handle_error2(err, stderr, FALSE, "svn: ");
  svn_error_clear(err);
}