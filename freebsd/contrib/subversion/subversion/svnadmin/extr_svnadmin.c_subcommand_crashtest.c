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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnadmin_opt_state {int /*<<< orphan*/  repository_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  crashtest_malfunction_handler ; 
 int /*<<< orphan*/  open_repos (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct svnadmin_opt_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_set_malfunction_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
subcommand_crashtest(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnadmin_opt_state *opt_state = baton;
  svn_repos_t *repos;

  (void)svn_error_set_malfunction_handler(crashtest_malfunction_handler);
  SVN_ERR(open_repos(&repos, opt_state->repository_path, opt_state, pool));
  SVN_ERR(svn_cmdline_printf(pool,
                             _("Successfully opened repository '%s'.\n"
                               "Will now crash to simulate a crashing "
                               "server process.\n"),
                             svn_dirent_local_style(opt_state->repository_path,
                                                    pool)));
  SVN_ERR_MALFUNCTION();

  /* merely silence a compiler warning (this will never be executed) */
  return SVN_NO_ERROR;
}