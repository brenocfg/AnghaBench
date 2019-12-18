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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline_fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
help(FILE *stream, apr_pool_t *pool)
{
  svn_error_clear(svn_cmdline_fputs(
    _("usage: svnmucc ACTION...\n"
      "Subversion multiple URL command client.\n"
      "Type 'svnmucc --version' to see the program version and RA modules.\n"
      "\n"
      "  Perform one or more Subversion repository URL-based ACTIONs, committing\n"
      "  the result as a (single) new revision.\n"
      "\n"
      "Actions:\n"
      "  cp REV SRC-URL DST-URL : copy SRC-URL@REV to DST-URL\n"
      "  mkdir URL              : create new directory URL\n"
      "  mv SRC-URL DST-URL     : move SRC-URL to DST-URL\n"
      "  rm URL                 : delete URL\n"
      "  put SRC-FILE URL       : add or modify file URL with contents copied from\n"
      "                           SRC-FILE (use \"-\" to read from standard input)\n"
      "  propset NAME VALUE URL : set property NAME on URL to VALUE\n"
      "  propsetf NAME FILE URL : set property NAME on URL to value read from FILE\n"
      "  propdel NAME URL       : delete property NAME from URL\n"
      "\n"
      "Valid options:\n"
      "  -h, -? [--help]        : display this text\n"
      "  -m [--message] ARG     : use ARG as a log message\n"
      "  -F [--file] ARG        : read log message from file ARG\n"
      "  -u [--username] ARG    : commit the changes as username ARG\n"
      "  -p [--password] ARG    : use ARG as the password\n"
      "  --password-from-stdin  : read password from stdin\n"
      "  -U [--root-url] ARG    : interpret all action URLs relative to ARG\n"
      "  -r [--revision] ARG    : use revision ARG as baseline for changes\n"
      "  --with-revprop ARG     : set revision property in the following format:\n"
      "                               NAME[=VALUE]\n"
      "  --non-interactive      : do no interactive prompting (default is to\n"
      "                           prompt only if standard input is a terminal)\n"
      "  --force-interactive    : do interactive prompting even if standard\n"
      "                           input is not a terminal\n"
      "  --trust-server-cert    : deprecated;\n"
      "                           same as --trust-server-cert-failures=unknown-ca\n"
      "  --trust-server-cert-failures ARG\n"
      "                           with --non-interactive, accept SSL server\n"
      "                           certificates with failures; ARG is comma-separated\n"
      "                           list of 'unknown-ca' (Unknown Authority),\n"
      "                           'cn-mismatch' (Hostname mismatch), 'expired'\n"
      "                           (Expired certificate),'not-yet-valid' (Not yet\n"
      "                           valid certificate) and 'other' (all other not\n"
      "                           separately classified certificate errors).\n"
      "  -X [--extra-args] ARG  : append arguments from file ARG (one per line;\n"
      "                           use \"-\" to read from standard input)\n"
      "  --config-dir ARG       : use ARG to override the config directory\n"
      "  --config-option ARG    : use ARG to override a configuration option\n"
      "  --no-auth-cache        : do not cache authentication tokens\n"
      "  --version              : print version information\n"),
                  stream, pool));
}