#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  quiet; int /*<<< orphan*/  version; } ;
typedef  TYPE_2__ opt_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_opt_print_help4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_print_modules (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnsync_cmd_table ; 
 int /*<<< orphan*/  svnsync_options ; 

__attribute__((used)) static svn_error_t *
help_cmd(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  opt_baton_t *opt_baton = baton;

  const char *header =
    _("general usage: svnsync SUBCOMMAND DEST_URL  [ARGS & OPTIONS ...]\n"
      "Subversion repository replication tool.\n"
      "Type 'svnsync help <subcommand>' for help on a specific subcommand.\n"
      "Type 'svnsync --version' to see the program version and RA modules.\n"
      "\n"
      "Available subcommands:\n");

  const char *ra_desc_start
    = _("The following repository access (RA) modules are available:\n\n");

  svn_stringbuf_t *version_footer = svn_stringbuf_create(ra_desc_start,
                                                         pool);

  SVN_ERR(svn_ra_print_modules(version_footer, pool));

  SVN_ERR(svn_opt_print_help4(os, "svnsync",
                              opt_baton ? opt_baton->version : FALSE,
                              opt_baton ? opt_baton->quiet : FALSE,
                              /*###opt_state ? opt_state->verbose :*/ FALSE,
                              version_footer->data, header,
                              svnsync_cmd_table, svnsync_options, NULL,
                              NULL, pool));

  return SVN_NO_ERROR;
}