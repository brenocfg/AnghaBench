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
typedef  int /*<<< orphan*/  svn_opt_subcommand_desc2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
typedef  int /*<<< orphan*/  apr_getopt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_print_help4 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt_print_help2(apr_getopt_t *os,
                    const char *pgm_name,
                    svn_boolean_t print_version,
                    svn_boolean_t quiet,
                    const char *version_footer,
                    const char *header,
                    const svn_opt_subcommand_desc2_t *cmd_table,
                    const apr_getopt_option_t *option_table,
                    const char *footer,
                    apr_pool_t *pool)
{
  return svn_error_trace(svn_opt_print_help4(os,
                                             pgm_name,
                                             print_version,
                                             quiet,
                                             FALSE,
                                             version_footer,
                                             header,
                                             cmd_table,
                                             option_table,
                                             NULL,
                                             footer,
                                             pool));
}