#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_11__ {scalar_t__ depth; scalar_t__ accept_which; scalar_t__ non_interactive; int /*<<< orphan*/  targets; } ;
typedef  TYPE_1__ svn_cl__opt_state_t ;
typedef  int /*<<< orphan*/  svn_cl__conflict_stats_t ;
struct TYPE_12__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * conflict_stats; TYPE_1__* opt_state; } ;
typedef  TYPE_2__ svn_cl__cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
struct TYPE_13__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ svn_cl__accept_edit ; 
 scalar_t__ svn_cl__accept_launch ; 
 scalar_t__ svn_cl__accept_postpone ; 
 scalar_t__ svn_cl__accept_unspecified ; 
 int /*<<< orphan*/  svn_cl__args_to_target_array_print_reserved (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__check_targets_are_local_paths (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_cl__eat_peg_revisions (TYPE_3__**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__walk_conflicts (TYPE_3__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_push_implicit_dot_target (TYPE_3__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__resolve(apr_getopt_t *os,
                void *baton,
                apr_pool_t *scratch_pool)
{
  svn_cl__opt_state_t *opt_state = ((svn_cl__cmd_baton_t *) baton)->opt_state;
  svn_cl__conflict_stats_t *conflict_stats =
    ((svn_cl__cmd_baton_t *) baton)->conflict_stats;
  svn_client_ctx_t *ctx = ((svn_cl__cmd_baton_t *) baton)->ctx;
  apr_array_header_t *targets;

  SVN_ERR(svn_cl__args_to_target_array_print_reserved(&targets, os,
                                                      opt_state->targets,
                                                      ctx, FALSE,
                                                      scratch_pool));
  if (! targets->nelts)
    svn_opt_push_implicit_dot_target(targets, scratch_pool);

  if (opt_state->depth == svn_depth_unknown)
    {
      if (opt_state->accept_which == svn_cl__accept_unspecified)
        opt_state->depth = svn_depth_infinity;
      else
        opt_state->depth = svn_depth_empty;
    }

  SVN_ERR(svn_cl__eat_peg_revisions(&targets, targets, scratch_pool));

  SVN_ERR(svn_cl__check_targets_are_local_paths(targets));

  if (opt_state->accept_which == svn_cl__accept_unspecified &&
      opt_state->non_interactive)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("missing --accept option"));
    }
  else if (opt_state->accept_which == svn_cl__accept_postpone ||
           opt_state->accept_which == svn_cl__accept_edit ||
           opt_state->accept_which == svn_cl__accept_launch)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("invalid 'accept' ARG"));
    }

  SVN_ERR(svn_cl__walk_conflicts(targets, conflict_stats,
                                 opt_state, ctx, scratch_pool));

  return SVN_NO_ERROR;
}