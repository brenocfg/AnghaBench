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
typedef  int /*<<< orphan*/  svnlook_ctxt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnlook_opt_state {int /*<<< orphan*/  show_inherited_props; int /*<<< orphan*/  verbose; int /*<<< orphan*/ * arg2; scalar_t__ revprop; int /*<<< orphan*/ * arg1; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ ind; scalar_t__ argc; } ;
typedef  TYPE_1__ apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  SVN_ERR_CL_INSUFFICIENT_ARGS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  do_pget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ctxt_baton (int /*<<< orphan*/ **,struct svnlook_opt_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
subcommand_pget(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnlook_opt_state *opt_state = baton;
  svnlook_ctxt_t *c;

  if (opt_state->arg1 == NULL)
    {
      return svn_error_createf
        (SVN_ERR_CL_INSUFFICIENT_ARGS, NULL,
         opt_state->revprop ?  _("Missing propname argument") :
         _("Missing propname and repository path arguments"));
    }
  else if (!opt_state->revprop && opt_state->arg2 == NULL)
    {
      return svn_error_create
        (SVN_ERR_CL_INSUFFICIENT_ARGS, NULL,
         _("Missing propname or repository path argument"));
    }
  if ((opt_state->revprop && opt_state->arg2 != NULL)
      || os->ind < os->argc)
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                            _("Too many arguments given"));

  SVN_ERR(get_ctxt_baton(&c, opt_state, pool));
  SVN_ERR(do_pget(c, opt_state->arg1,
                  opt_state->revprop ? NULL : opt_state->arg2,
                  opt_state->verbose, opt_state->show_inherited_props,
                  pool));
  return SVN_NO_ERROR;
}