#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_21__ {int /*<<< orphan*/  log_msg_baton3; scalar_t__ log_msg_func3; int /*<<< orphan*/  config; int /*<<< orphan*/ * notify_func2; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_22__ {scalar_t__ depth; scalar_t__ quiet; int /*<<< orphan*/  dry_run; int /*<<< orphan*/  keep_local; int /*<<< orphan*/  changelists; int /*<<< orphan*/  targets; scalar_t__ remove; scalar_t__ list; } ;
typedef  TYPE_2__ svn_cl__opt_state_t ;
struct TYPE_23__ {TYPE_1__* ctx; TYPE_2__* opt_state; } ;
typedef  TYPE_3__ svn_cl__cmd_baton_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_24__ {scalar_t__ ind; scalar_t__ argc; } ;
typedef  TYPE_4__ apr_getopt_t ;
struct TYPE_25__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_5__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  SVN_ERR_CL_INSUFFICIENT_ARGS ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * get_name (char const**,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shelves_list (char const*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__args_to_target_array_print_reserved (TYPE_5__**,TYPE_4__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__check_targets_are_local_paths (TYPE_5__*) ; 
 int /*<<< orphan*/ * svn_cl__cleanup_log_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__eat_peg_revisions (TYPE_5__**,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__make_log_msg_baton (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_shelf_has_changes (int /*<<< orphan*/ *,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_shelve (char const*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_shelves_delete (char const*,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/ * svn_dirent_get_absolute (char const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_push_implicit_dot_target (TYPE_5__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__shelve(apr_getopt_t *os,
               void *baton,
               apr_pool_t *pool)
{
  svn_cl__opt_state_t *opt_state = ((svn_cl__cmd_baton_t *) baton)->opt_state;
  svn_client_ctx_t *ctx = ((svn_cl__cmd_baton_t *) baton)->ctx;
  const char *local_abspath;
  const char *name;
  apr_array_header_t *targets;
  svn_boolean_t has_changes;

  if (opt_state->quiet)
    ctx->notify_func2 = NULL; /* Easy out: avoid unneeded work */

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, "", pool));

  if (opt_state->list)
    {
      if (os->ind < os->argc)
        return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, 0, NULL);

      SVN_ERR(shelves_list(local_abspath,
                           ! opt_state->quiet /*diffstat*/,
                           ctx, pool));
      return SVN_NO_ERROR;
    }

  SVN_ERR(get_name(&name, os, pool, pool));

  if (opt_state->remove)
    {
      if (os->ind < os->argc)
        return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, 0, NULL);

      SVN_ERR(svn_client_shelves_delete(name, local_abspath,
                                        opt_state->dry_run,
                                        ctx, pool));
      if (! opt_state->quiet)
        SVN_ERR(svn_cmdline_printf(pool, "deleted '%s'\n", name));
      return SVN_NO_ERROR;
    }

  /* Parse the remaining arguments as paths. */
  SVN_ERR(svn_cl__args_to_target_array_print_reserved(&targets, os,
                                                      opt_state->targets,
                                                      ctx, FALSE, pool));
  svn_opt_push_implicit_dot_target(targets, pool);

  {
      svn_depth_t depth = opt_state->depth;
      svn_error_t *err;

      /* shelve has no implicit dot-target `.', so don't you put that
         code here! */
      if (!targets->nelts)
        return svn_error_create(SVN_ERR_CL_INSUFFICIENT_ARGS, 0, NULL);

      SVN_ERR(svn_cl__check_targets_are_local_paths(targets));

      if (depth == svn_depth_unknown)
        depth = svn_depth_infinity;

      SVN_ERR(svn_cl__eat_peg_revisions(&targets, targets, pool));

      if (ctx->log_msg_func3)
        SVN_ERR(svn_cl__make_log_msg_baton(&ctx->log_msg_baton3,
                                           opt_state, NULL, ctx->config,
                                           pool));
      err = svn_client_shelve(name,
                              targets, depth, opt_state->changelists,
                              opt_state->keep_local, opt_state->dry_run,
                              ctx, pool);
      if (ctx->log_msg_func3)
        SVN_ERR(svn_cl__cleanup_log_msg(ctx->log_msg_baton3,
                                        err, pool));
      else
        SVN_ERR(err);
  }

  /* If no modifications were shelved, throw an error. */
  SVN_ERR(svn_client_shelf_has_changes(&has_changes,
                                       name, local_abspath, ctx, pool));
  if (! has_changes)
    {
      SVN_ERR(svn_client_shelves_delete(name, local_abspath,
                                        opt_state->dry_run, ctx, pool));
      return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                               _("No changes were shelved"));
    }

  if (! opt_state->quiet)
    SVN_ERR(svn_cmdline_printf(pool, "shelved '%s'\n", name));

  return SVN_NO_ERROR;
}