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
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svnlook_ctxt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnlook_opt_state {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_number_of_args (struct svnlook_opt_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ctxt_baton (TYPE_1__**,struct svnlook_opt_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_fs_get_uuid (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
subcommand_uuid(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnlook_opt_state *opt_state = baton;
  svnlook_ctxt_t *c;
  const char *uuid;

  SVN_ERR(check_number_of_args(opt_state, 0));

  SVN_ERR(get_ctxt_baton(&c, opt_state, pool));
  SVN_ERR(svn_fs_get_uuid(c->fs, &uuid, pool));
  SVN_ERR(svn_cmdline_printf(pool, "%s\n", uuid));
  return SVN_NO_ERROR;
}