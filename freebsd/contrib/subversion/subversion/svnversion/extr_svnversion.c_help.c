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
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ description; } ;
typedef  TYPE_1__ apr_getopt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_format_option (char const**,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
help(const apr_getopt_option_t *options, apr_pool_t *pool)
{
  svn_error_clear
    (svn_cmdline_fprintf
     (stdout, pool,
      _("usage: svnversion [OPTIONS] [WC_PATH [TRAIL_URL]]\n"
        "Subversion working copy identification tool.\n"
        "Type 'svnversion --version' to see the program version.\n"
        "\n"
        "  Produce a compact version identifier for the working copy path\n"
        "  WC_PATH.  TRAIL_URL is the trailing portion of the URL used to\n"
        "  determine if WC_PATH itself is switched (detection of switches\n"
        "  within WC_PATH does not rely on TRAIL_URL).  The version identifier\n"
        "  is written to standard output.  For example:\n"
        "\n"
        "    $ svnversion . /repos/svn/trunk\n"
        "    4168\n"
        "\n"
        "  The version identifier will be a single number if the working\n"
        "  copy is single revision, unmodified, not switched and with\n"
        "  a URL that matches the TRAIL_URL argument.  If the working\n"
        "  copy is unusual the version identifier will be more complex:\n"
        "\n"
        "   4123:4168     mixed revision working copy\n"
        "   4168M         modified working copy\n"
        "   4123S         switched working copy\n"
        "   4123P         partial working copy, from a sparse checkout\n"
        "   4123:4168MS   mixed revision, modified, switched working copy\n"
        "\n"
        "  If WC_PATH is an unversioned path, the program will output\n"
        "  'Unversioned directory' or 'Unversioned file'.  If WC_PATH is\n"
        "  an added or copied or moved path, the program will output\n"
        "  'Uncommitted local addition, copy or move'.\n"
        "\n"
        "  If invoked without arguments WC_PATH will be the current directory.\n"
        "\n"
        "Valid options:\n")));
  while (options->description)
    {
      const char *optstr;
      svn_opt_format_option(&optstr, options, TRUE, pool);
      svn_error_clear(svn_cmdline_fprintf(stdout, pool, "  %s\n", optstr));
      ++options;
    }
  svn_error_clear(svn_cmdline_fprintf(stdout, pool, "\n"));
}