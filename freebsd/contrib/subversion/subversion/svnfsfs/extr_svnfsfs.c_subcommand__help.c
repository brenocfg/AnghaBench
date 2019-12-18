#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  quiet; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ svnfsfs__opt_state ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  cmd_table ; 
 int /*<<< orphan*/  options_table ; 
 int /*<<< orphan*/  svn_opt_print_help4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
subcommand__help(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  svnfsfs__opt_state *opt_state = baton;
  const char *header =
    _("general usage: svnfsfs SUBCOMMAND REPOS_PATH  [ARGS & OPTIONS ...]\n"
      "Subversion FSFS repository manipulation tool.\n"
      "Type 'svnfsfs help <subcommand>' for help on a specific subcommand.\n"
      "Type 'svnfsfs --version' to see the program version.\n"
      "\n"
      "Available subcommands:\n");

  SVN_ERR(svn_opt_print_help4(os, "svnfsfs",
                              opt_state ? opt_state->version : FALSE,
                              opt_state ? opt_state->quiet : FALSE,
                              /*###opt_state ? opt_state->verbose :*/ FALSE,
                              NULL,
                              header, cmd_table, options_table, NULL, NULL,
                              pool));

  return SVN_NO_ERROR;
}