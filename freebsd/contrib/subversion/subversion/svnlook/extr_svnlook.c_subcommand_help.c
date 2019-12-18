#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnlook_opt_state {int /*<<< orphan*/  verbose; int /*<<< orphan*/  quiet; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  cmd_table ; 
 int /*<<< orphan*/  options_table ; 
 int /*<<< orphan*/  svn_fs_print_modules (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_opt_print_help4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
subcommand_help(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnlook_opt_state *opt_state = baton;
  const char *header =
    _("general usage: svnlook SUBCOMMAND REPOS_PATH [ARGS & OPTIONS ...]\n"
      "Subversion repository inspection tool.\n"
      "Type 'svnlook help <subcommand>' for help on a specific subcommand.\n"
      "Type 'svnlook --version' to see the program version and FS modules.\n"
      "Note: any subcommand which takes the '--revision' and '--transaction'\n"
      "      options will, if invoked without one of those options, act on\n"
      "      the repository's youngest revision.\n"
      "\n"
      "Available subcommands:\n");

  const char *fs_desc_start
    = _("The following repository back-end (FS) modules are available:\n\n");

  svn_stringbuf_t *version_footer;

  version_footer = svn_stringbuf_create(fs_desc_start, pool);
  SVN_ERR(svn_fs_print_modules(version_footer, pool));

  SVN_ERR(svn_opt_print_help4(os, "svnlook",
                              opt_state ? opt_state->version : FALSE,
                              opt_state ? opt_state->quiet : FALSE,
                              opt_state ? opt_state->verbose : FALSE,
                              version_footer->data,
                              header, cmd_table, options_table, NULL,
                              NULL, pool));

  return SVN_NO_ERROR;
}