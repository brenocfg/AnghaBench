#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_opt_subcommand_desc2_t ;
struct TYPE_6__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_ERR_IO_PIPE_WRITE_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* print_command_info2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__* svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_handle_error2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * svn_opt_get_canonical_subcommand2 (int /*<<< orphan*/  const*,char const*) ; 

void
svn_opt_subcommand_help3(const char *subcommand,
                         const svn_opt_subcommand_desc2_t *table,
                         const apr_getopt_option_t *options_table,
                         const int *global_options,
                         apr_pool_t *pool)
{
  const svn_opt_subcommand_desc2_t *cmd =
    svn_opt_get_canonical_subcommand2(table, subcommand);
  svn_error_t *err;

  if (cmd)
    err = print_command_info2(cmd, options_table, global_options,
                              TRUE, pool, stdout);
  else
    err = svn_cmdline_fprintf(stderr, pool,
                              _("\"%s\": unknown command.\n\n"), subcommand);

  if (err) {
    /* Issue #3014: Don't print anything on broken pipes. */
    if (err->apr_err != SVN_ERR_IO_PIPE_WRITE_ERROR)
      svn_handle_error2(err, stderr, FALSE, "svn: ");
    svn_error_clear(err);
  }
}