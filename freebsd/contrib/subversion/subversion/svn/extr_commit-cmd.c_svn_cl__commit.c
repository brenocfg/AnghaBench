#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
struct TYPE_16__ {int /*<<< orphan*/  log_msg_baton3; struct copy_warning_notify_baton* notify_baton2; int /*<<< orphan*/  notify_func2; scalar_t__ config; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_17__ {scalar_t__ depth; scalar_t__ quiet; int /*<<< orphan*/  revprop_table; int /*<<< orphan*/  changelists; int /*<<< orphan*/  include_externals; int /*<<< orphan*/  keep_changelists; int /*<<< orphan*/  targets; } ;
typedef  TYPE_2__ svn_cl__opt_state_t ;
struct TYPE_18__ {TYPE_1__* ctx; TYPE_2__* opt_state; } ;
typedef  TYPE_3__ svn_cl__cmd_baton_t ;
typedef  void* svn_boolean_t ;
struct copy_warning_notify_baton {scalar_t__ depth; void* warned; struct copy_warning_notify_baton* wrapped_baton; int /*<<< orphan*/  wrapped_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
struct TYPE_19__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_4__ apr_array_header_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_NO_UNLOCK ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_MISCELLANY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  copy_warning_notify_func ; 
 int /*<<< orphan*/  svn_cl__args_to_target_array_print_reserved (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__check_targets_are_local_paths (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_cl__cleanup_log_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__eat_peg_revisions (TYPE_4__**,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__make_log_msg_baton (int /*<<< orphan*/ *,TYPE_2__*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__print_commit_info ; 
 int /*<<< orphan*/ * svn_client_commit6 (TYPE_4__*,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_condense_targets (char const**,TYPE_4__**,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt_push_implicit_dot_target (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_actual_target2 (char const**,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__commit(apr_getopt_t *os,
               void *baton,
               apr_pool_t *pool)
{
  svn_error_t *err;
  svn_cl__opt_state_t *opt_state = ((svn_cl__cmd_baton_t *) baton)->opt_state;
  svn_client_ctx_t *ctx = ((svn_cl__cmd_baton_t *) baton)->ctx;
  apr_array_header_t *targets;
  apr_array_header_t *condensed_targets;
  const char *base_dir;
  svn_config_t *cfg;
  svn_boolean_t no_unlock = FALSE;
  struct copy_warning_notify_baton cwnb;

  SVN_ERR(svn_cl__args_to_target_array_print_reserved(&targets, os,
                                                      opt_state->targets,
                                                      ctx, FALSE, pool));

  SVN_ERR_W(svn_cl__check_targets_are_local_paths(targets),
            _("Commit targets must be local paths"));

  /* Add "." if user passed 0 arguments. */
  svn_opt_push_implicit_dot_target(targets, pool);

  SVN_ERR(svn_cl__eat_peg_revisions(&targets, targets, pool));

  /* Condense the targets (like commit does)... */
  SVN_ERR(svn_dirent_condense_targets(&base_dir, &condensed_targets, targets,
                                      TRUE, pool, pool));

  if ((! condensed_targets) || (! condensed_targets->nelts))
    {
      const char *parent_dir, *base_name;

      SVN_ERR(svn_wc_get_actual_target2(&parent_dir, &base_name, ctx->wc_ctx,
                                        base_dir, pool, pool));
      if (*base_name)
        base_dir = apr_pstrdup(pool, parent_dir);
    }

  if (opt_state->depth == svn_depth_unknown)
    opt_state->depth = svn_depth_infinity;

  cfg = ctx->config
           ? svn_hash_gets(ctx->config, SVN_CONFIG_CATEGORY_CONFIG)
           : NULL;
  if (cfg)
    SVN_ERR(svn_config_get_bool(cfg, &no_unlock,
                                SVN_CONFIG_SECTION_MISCELLANY,
                                SVN_CONFIG_OPTION_NO_UNLOCK, FALSE));

  /* We're creating a new log message baton because we can use our base_dir
     to store the temp file, instead of the current working directory.  The
     client might not have write access to their working directory, but they
     better have write access to the directory they're committing.  */
  SVN_ERR(svn_cl__make_log_msg_baton(&(ctx->log_msg_baton3),
                                     opt_state, base_dir,
                                     ctx->config, pool));

  /* Copies are done server-side, and cheaply, which means they're
     effectively always done with infinite depth.  This is a potential
     cause of confusion for users trying to commit copied subtrees in
     part by restricting the commit's depth.  See issues #3699 and #3752. */
  if (opt_state->depth < svn_depth_infinity)
    {
      cwnb.wrapped_func = ctx->notify_func2;
      cwnb.wrapped_baton = ctx->notify_baton2;
      cwnb.depth = opt_state->depth;
      cwnb.warned = FALSE;
      ctx->notify_func2 = copy_warning_notify_func;
      ctx->notify_baton2 = &cwnb;
    }

  /* Commit. */
  err = svn_client_commit6(targets,
                           opt_state->depth,
                           no_unlock,
                           opt_state->keep_changelists,
                           TRUE /* commit_as_operations */,
                           opt_state->include_externals, /* file externals */
                           opt_state->include_externals, /* dir externals */
                           opt_state->changelists,
                           opt_state->revprop_table,
                           (opt_state->quiet
                            ? NULL : svn_cl__print_commit_info),
                           NULL,
                           ctx,
                           pool);
  SVN_ERR(svn_cl__cleanup_log_msg(ctx->log_msg_baton3, err, pool));

  return SVN_NO_ERROR;
}