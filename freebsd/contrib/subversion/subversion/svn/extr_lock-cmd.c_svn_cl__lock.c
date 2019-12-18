#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {struct notify_lock_baton_t* notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_15__ {int /*<<< orphan*/  force; int /*<<< orphan*/  targets; } ;
typedef  TYPE_2__ svn_cl__opt_state_t ;
struct TYPE_16__ {TYPE_1__* ctx; TYPE_2__* opt_state; } ;
typedef  TYPE_3__ svn_cl__cmd_baton_t ;
struct notify_lock_baton_t {scalar_t__ had_failure; struct notify_lock_baton_t* inner_baton; int /*<<< orphan*/  inner_notify; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
struct TYPE_17__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_4__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_INSUFFICIENT_ARGS ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  get_comment (char const**,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_lock_handler ; 
 int /*<<< orphan*/  svn_cl__args_to_target_array_print_reserved (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__assert_homogeneous_target_type (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_cl__eat_peg_revisions (TYPE_4__**,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_lock (TYPE_4__*,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__lock(apr_getopt_t *os,
             void *baton,
             apr_pool_t *pool)
{
  svn_cl__opt_state_t *opt_state = ((svn_cl__cmd_baton_t *) baton)->opt_state;
  svn_client_ctx_t *ctx = ((svn_cl__cmd_baton_t *) baton)->ctx;
  apr_array_header_t *targets;
  const char *comment;
  struct notify_lock_baton_t nlb;

  SVN_ERR(svn_cl__args_to_target_array_print_reserved(&targets, os,
                                                      opt_state->targets,
                                                      ctx, FALSE, pool));

  /* We only support locking files, so '.' is not valid. */
  if (! targets->nelts)
    return svn_error_create(SVN_ERR_CL_INSUFFICIENT_ARGS, 0, NULL);

  SVN_ERR(svn_cl__assert_homogeneous_target_type(targets));

  /* Get comment. */
  SVN_ERR(get_comment(&comment, ctx, opt_state, pool));

  SVN_ERR(svn_cl__eat_peg_revisions(&targets, targets, pool));

  nlb.inner_notify = ctx->notify_func2;
  nlb.inner_baton = ctx->notify_baton2;
  nlb.had_failure = FALSE;

  ctx->notify_func2 = notify_lock_handler;
  ctx->notify_baton2 = &nlb;

  SVN_ERR(svn_client_lock(targets, comment, opt_state->force, ctx, pool));

  if (nlb.had_failure)
    return svn_error_create(SVN_ERR_ILLEGAL_TARGET, NULL,
                            _("One or more locks could not be obtained"));

  return SVN_NO_ERROR;
}