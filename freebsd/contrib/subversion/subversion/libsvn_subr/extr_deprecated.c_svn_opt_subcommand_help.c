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
typedef  int /*<<< orphan*/  svn_opt_subcommand_desc_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * print_command_info (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_handle_error2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * svn_opt_get_canonical_subcommand (int /*<<< orphan*/  const*,char const*) ; 

void
svn_opt_subcommand_help(const char *subcommand,
                        const svn_opt_subcommand_desc_t *table,
                        const apr_getopt_option_t *options_table,
                        apr_pool_t *pool)
{
  const svn_opt_subcommand_desc_t *cmd =
    svn_opt_get_canonical_subcommand(table, subcommand);
  svn_error_t *err;

  if (cmd)
    err = print_command_info(cmd, options_table, TRUE, pool, stdout);
  else
    err = svn_cmdline_fprintf(stderr, pool,
                              _("\"%s\": unknown command.\n\n"), subcommand);

  if (err) {
    svn_handle_error2(err, stderr, FALSE, "svn: ");
    svn_error_clear(err);
  }
}