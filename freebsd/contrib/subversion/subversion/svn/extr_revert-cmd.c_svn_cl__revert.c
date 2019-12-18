#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_18__ {scalar_t__ depth; int /*<<< orphan*/  changelists; int /*<<< orphan*/  targets; } ;
typedef  TYPE_2__ svn_cl__opt_state_t ;
struct TYPE_19__ {int /*<<< orphan*/ * ctx; TYPE_2__* opt_state; } ;
typedef  TYPE_3__ svn_cl__cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
struct TYPE_20__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_4__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_DEPTH_IS_RECURSIVE (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_INSUFFICIENT_ARGS ; 
 scalar_t__ SVN_ERR_WC_INVALID_OPERATION_DEPTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cl__args_to_target_array_print_reserved (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__check_targets_are_local_paths (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_cl__eat_peg_revisions (TYPE_4__**,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client_revert3 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_unknown ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_quick_wrap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

svn_error_t *
svn_cl__revert(apr_getopt_t *os,
               void *baton,
               apr_pool_t *scratch_pool)
{
  svn_cl__opt_state_t *opt_state = ((svn_cl__cmd_baton_t *) baton)->opt_state;
  svn_client_ctx_t *ctx = ((svn_cl__cmd_baton_t *) baton)->ctx;
  apr_array_header_t *targets = NULL;
  svn_error_t *err;

  SVN_ERR(svn_cl__args_to_target_array_print_reserved(&targets, os,
                                                      opt_state->targets,
                                                      ctx, FALSE,
                                                      scratch_pool));

  /* Revert has no implicit dot-target `.', so don't you put that code here! */
  if (! targets->nelts)
    return svn_error_create(SVN_ERR_CL_INSUFFICIENT_ARGS, 0, NULL);

  /* Revert is especially conservative, by default it is as
     nonrecursive as possible. */
  if (opt_state->depth == svn_depth_unknown)
    opt_state->depth = svn_depth_empty;

  SVN_ERR(svn_cl__eat_peg_revisions(&targets, targets, scratch_pool));

  SVN_ERR(svn_cl__check_targets_are_local_paths(targets));

  err = svn_client_revert3(targets, opt_state->depth,
                           opt_state->changelists,
                           FALSE /* clear_changelists */,
                           FALSE /* metadata_only */,
                           ctx, scratch_pool);
  if (err
      && (err->apr_err == SVN_ERR_WC_INVALID_OPERATION_DEPTH)
      && (! SVN_DEPTH_IS_RECURSIVE(opt_state->depth)))
    {
      err = svn_error_quick_wrap
        (err, _("Try 'svn revert --depth infinity' instead?"));
    }

  return svn_error_trace(err);
}