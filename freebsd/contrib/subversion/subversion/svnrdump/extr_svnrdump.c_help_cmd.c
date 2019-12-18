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
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/ * svn_opt_print_help4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnrdump__cmd_table ; 
 int /*<<< orphan*/  svnrdump__options ; 

__attribute__((used)) static svn_error_t *
help_cmd(apr_getopt_t *os,
         void *baton,
         apr_pool_t *pool)
{
  const char *header =
    _("general usage: svnrdump SUBCOMMAND URL [-r LOWER[:UPPER]]\n"
      "Subversion remote repository dump and load tool.\n"
      "Type 'svnrdump help <subcommand>' for help on a specific subcommand.\n"
      "Type 'svnrdump --version' to see the program version and RA modules.\n"
      "\n"
      "Available subcommands:\n");

  return svn_opt_print_help4(os, "svnrdump", FALSE, FALSE, FALSE, NULL,
                             header, svnrdump__cmd_table, svnrdump__options,
                             NULL, NULL, pool);
}