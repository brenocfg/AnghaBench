#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ optch; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_cmdline_fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_format_option (char const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svnserve__options ; 

__attribute__((used)) static void help(apr_pool_t *pool)
{
  apr_size_t i;

#ifdef WIN32
  svn_error_clear(svn_cmdline_fputs(_("usage: svnserve [-d | -i | -t | -X "
                                      "| --service] [options]\n"
                                      "Subversion repository server.\n"
                                      "Type 'svnserve --version' to see the "
                                      "program version.\n"
                                      "\n"
                                      "Valid options:\n"),
                                      stdout, pool));
#else
  svn_error_clear(svn_cmdline_fputs(_("usage: svnserve [-d | -i | -t | -X] "
                                      "[options]\n"
                                      "Subversion repository server.\n"
                                      "Type 'svnserve --version' to see the "
                                      "program version.\n"
                                      "\n"
                                      "Valid options:\n"),
                                      stdout, pool));
#endif
  for (i = 0; svnserve__options[i].name && svnserve__options[i].optch; i++)
    {
      const char *optstr;
      svn_opt_format_option(&optstr, svnserve__options + i, TRUE, pool);
      svn_error_clear(svn_cmdline_fprintf(stdout, pool, "  %s\n", optstr));
    }
  svn_error_clear(svn_cmdline_fprintf(stdout, pool, "\n"));
}