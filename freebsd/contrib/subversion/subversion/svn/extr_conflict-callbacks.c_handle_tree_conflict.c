#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  svn_cl__conflict_stats_t ;
typedef  int svn_boolean_t ;
struct client_option_t {scalar_t__ choice; int /*<<< orphan*/  label; } ;
struct TYPE_13__ {scalar_t__ choice; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ client_option_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 scalar_t__ SVN_ERR_WC_FOUND_CONFLICT ; 
 scalar_t__ SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/ * build_tree_conflict_options (TYPE_2__**,TYPE_2__**,TYPE_2__**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct client_option_t* find_recommended_option (TYPE_2__*) ; 
 int /*<<< orphan*/ * mark_conflict_resolved (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * prompt_move_target_path (int*,TYPE_2__*,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * prompt_user (TYPE_1__ const**,TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_cl__local_style_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_option_find_by_id (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_move_dir_merge ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_move_file_text_merge ; 
 scalar_t__ svn_client_conflict_option_postpone ; 
 int /*<<< orphan*/ * svn_client_conflict_option_set_moved_to_abspath (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_option_set_moved_to_repos_relpath (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_undefined ; 
 scalar_t__ svn_client_conflict_option_unspecified ; 
 int /*<<< orphan*/ * svn_client_conflict_tree_get_description (char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_tree_get_details (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_tree_get_resolution_options (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_root_cause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_tree_conflict(svn_boolean_t *resolved,
                     svn_boolean_t *postponed,
                     svn_boolean_t *quit,
                     svn_boolean_t *printed_description,
                     svn_client_conflict_t *conflict,
                     const char *path_prefix,
                     svn_cmdline_prompt_baton_t *pb,
                     svn_cl__conflict_stats_t *conflict_stats,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  apr_array_header_t *tree_conflict_options;
  svn_client_conflict_option_id_t option_id;
  const char *local_abspath;
  const char *conflict_description;
  const char *local_change_description;
  const char *incoming_change_description;
  apr_array_header_t *possible_moved_to_repos_relpaths;
  apr_array_header_t *possible_moved_to_abspaths;
  svn_boolean_t all_options_are_dumb;
  const struct client_option_t *recommended_option;
  svn_boolean_t repos_move_target_chosen = FALSE;
  svn_boolean_t wc_move_target_chosen = FALSE;

  option_id = svn_client_conflict_option_unspecified;
  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  /* Always show the best possible conflict description and options. */
  SVN_ERR(svn_client_conflict_tree_get_details(conflict, ctx, scratch_pool));

  SVN_ERR(svn_client_conflict_tree_get_description(
           &incoming_change_description, &local_change_description,
           conflict, ctx, scratch_pool, scratch_pool));
  conflict_description = apr_psprintf(scratch_pool, "%s\n%s",
                                      incoming_change_description,
                                      local_change_description);
  if (!*printed_description)
    SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                                _("Tree conflict on '%s':\n%s\n"),
                                svn_cl__local_style_skip_ancestor(
                                  path_prefix, local_abspath, scratch_pool),
                                conflict_description));

  SVN_ERR(build_tree_conflict_options(&tree_conflict_options,
                                      &possible_moved_to_repos_relpaths,
                                      &possible_moved_to_abspaths,
                                      &all_options_are_dumb,
                                      conflict, ctx,
                                      scratch_pool, scratch_pool));

  /* Try a recommended resolution option before prompting. */
  recommended_option = find_recommended_option(tree_conflict_options);
  if (recommended_option)
    {
      svn_error_t *err;
      apr_status_t root_cause;

      SVN_ERR(svn_cmdline_printf(scratch_pool,
                                 _("Applying recommended resolution '%s':\n"),
                                 recommended_option->label));

      err = mark_conflict_resolved(conflict, recommended_option->choice,
                                   FALSE, NULL, TRUE,
                                   path_prefix, conflict_stats,
                                   ctx, scratch_pool);
      if (!err)
        {
          *resolved = TRUE;
          return SVN_NO_ERROR;
        }

      root_cause = svn_error_root_cause(err)->apr_err;
      if (root_cause != SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE &&
          root_cause != SVN_ERR_WC_OBSTRUCTED_UPDATE &&
          root_cause != SVN_ERR_WC_FOUND_CONFLICT)
        return svn_error_trace(err);

      /* Fall back to interactive prompting. */
      svn_error_clear(err);
    }

  if (all_options_are_dumb)
    SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                                _("\nSubversion is not smart enough to resolve "
                                  "this tree conflict automatically!\nSee 'svn "
                                  "help resolve' for more information.\n\n")));

  iterpool = svn_pool_create(scratch_pool);
  while (1)
    {
      const client_option_t *opt;

      svn_pool_clear(iterpool);

      if (!repos_move_target_chosen &&
          possible_moved_to_repos_relpaths &&
          possible_moved_to_repos_relpaths->nelts > 1)
        SVN_ERR(svn_cmdline_printf(scratch_pool,
                  _("Ambiguous move destinations exist in the repository; "
                    "try the 'd' option\n")));
      if (!wc_move_target_chosen && possible_moved_to_abspaths &&
          possible_moved_to_abspaths->nelts > 1)
        SVN_ERR(svn_cmdline_printf(scratch_pool,
                  _("Ambiguous move destinations exist in the working copy; "
                    "try the 'w' option\n")));

      SVN_ERR(prompt_user(&opt, tree_conflict_options, NULL,
                          conflict_description, pb, iterpool));
      *printed_description = TRUE;
      if (! opt)
        continue;

      if (strcmp(opt->code, "q") == 0)
        {
          option_id = opt->choice;
          *quit = TRUE;
          break;
        }
      else if (strcmp(opt->code, "d") == 0)
        {
          int preferred_move_target_idx;
          apr_array_header_t *options;
          svn_client_conflict_option_t *conflict_option;

          SVN_ERR(prompt_move_target_path(&preferred_move_target_idx,
                                          possible_moved_to_repos_relpaths,
                                          FALSE,
                                          pb, local_abspath, ctx, iterpool));

          /* Update preferred move target path. */
          SVN_ERR(svn_client_conflict_tree_get_resolution_options(&options,
                                                                  conflict,
                                                                  ctx,
                                                                  iterpool,
                                                                  iterpool));
          conflict_option =
            svn_client_conflict_option_find_by_id( 
              options,
              svn_client_conflict_option_incoming_move_file_text_merge);
          if (conflict_option == NULL)
            {
              conflict_option =
                svn_client_conflict_option_find_by_id( 
                  options, svn_client_conflict_option_incoming_move_dir_merge);
            }

          if (conflict_option)
            {
              SVN_ERR(svn_client_conflict_option_set_moved_to_repos_relpath(
                        conflict_option, preferred_move_target_idx,
                        ctx, iterpool));
              repos_move_target_chosen = TRUE;
              wc_move_target_chosen = FALSE;

              /* Update option description. */
              SVN_ERR(build_tree_conflict_options(
                        &tree_conflict_options,
                        &possible_moved_to_repos_relpaths,
                        &possible_moved_to_abspaths,
                        NULL, conflict, ctx,
                        scratch_pool, scratch_pool));

              /* Update conflict description. */
              SVN_ERR(svn_client_conflict_tree_get_description(
                       &incoming_change_description, &local_change_description,
                       conflict, ctx, scratch_pool, scratch_pool));
              conflict_description = apr_psprintf(scratch_pool, "%s\n%s",
                                                  incoming_change_description,
                                                  local_change_description);
            }
          continue;
        }
      else if (strcmp(opt->code, "w") == 0)
        {
          int preferred_move_target_idx;
          apr_array_header_t *options;
          svn_client_conflict_option_t *conflict_option;

          SVN_ERR(prompt_move_target_path(&preferred_move_target_idx,
                                           possible_moved_to_abspaths, TRUE,
                                           pb, local_abspath, ctx, iterpool));

          /* Update preferred move target path. */
          SVN_ERR(svn_client_conflict_tree_get_resolution_options(&options,
                                                                  conflict,
                                                                  ctx,
                                                                  iterpool,
                                                                  iterpool));
          conflict_option =
            svn_client_conflict_option_find_by_id( 
              options,
              svn_client_conflict_option_incoming_move_file_text_merge);
          if (conflict_option == NULL)
            {
              conflict_option =
                svn_client_conflict_option_find_by_id( 
                  options, svn_client_conflict_option_incoming_move_dir_merge);
            }

          if (conflict_option)
            {
              SVN_ERR(svn_client_conflict_option_set_moved_to_abspath(
                        conflict_option, preferred_move_target_idx, ctx,
                        iterpool));
              wc_move_target_chosen = TRUE;

              /* Update option description. */
              SVN_ERR(build_tree_conflict_options(
                        &tree_conflict_options,
                        &possible_moved_to_repos_relpaths,
                        &possible_moved_to_abspaths,
                        NULL, conflict, ctx,
                        scratch_pool, scratch_pool));
            }
          continue;
        }
      else if (opt->choice != svn_client_conflict_option_undefined)
        {
          option_id = opt->choice;
          break;
        }
    }
  svn_pool_destroy(iterpool);
  if (option_id != svn_client_conflict_option_unspecified &&
      option_id != svn_client_conflict_option_postpone)
    {
      SVN_ERR(mark_conflict_resolved(conflict, option_id,
                                     FALSE, NULL, TRUE,
                                     path_prefix, conflict_stats,
                                     ctx, scratch_pool));
      *resolved = TRUE;
    }
  else
    {
      *resolved = FALSE;
      *postponed = (option_id == svn_client_conflict_option_postpone);
    }

  return SVN_NO_ERROR;
}