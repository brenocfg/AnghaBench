#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_25__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton_t ;
struct TYPE_26__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  svn_cl__conflict_stats_t ;
typedef  scalar_t__ svn_cl__accept_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_27__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_CL_NO_EXTERNAL_EDITOR ; 
 scalar_t__ SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL ; 
 scalar_t__ SVN_ERR_EXTERNAL_PROGRAM ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 scalar_t__ SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_1__* mark_conflict_resolved (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*,scalar_t__,char const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* resolve_conflict_interactively (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ svn_cl__accept_base ; 
 scalar_t__ svn_cl__accept_edit ; 
 scalar_t__ svn_cl__accept_launch ; 
 scalar_t__ svn_cl__accept_mine_conflict ; 
 scalar_t__ svn_cl__accept_mine_full ; 
 scalar_t__ svn_cl__accept_postpone ; 
 scalar_t__ svn_cl__accept_recommended ; 
 scalar_t__ svn_cl__accept_theirs_conflict ; 
 scalar_t__ svn_cl__accept_theirs_full ; 
 scalar_t__ svn_cl__accept_unspecified ; 
 scalar_t__ svn_cl__accept_working ; 
 TYPE_1__* svn_cl__merge_file_externally (char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client_conflict_get_conflicted (scalar_t__*,TYPE_3__**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_incoming_change (int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_recommended_option_id (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_accept_current_wc_state ; 
 scalar_t__ svn_client_conflict_option_base_text ; 
 scalar_t__ svn_client_conflict_option_incoming_text ; 
 scalar_t__ svn_client_conflict_option_incoming_text_where_conflicted ; 
 scalar_t__ svn_client_conflict_option_merged_text ; 
 scalar_t__ svn_client_conflict_option_postpone ; 
 scalar_t__ svn_client_conflict_option_unspecified ; 
 scalar_t__ svn_client_conflict_option_update_any_moved_away_children ; 
 scalar_t__ svn_client_conflict_option_update_move_destination ; 
 scalar_t__ svn_client_conflict_option_working_text ; 
 scalar_t__ svn_client_conflict_option_working_text_where_conflicted ; 
 TYPE_1__* svn_client_conflict_text_get_contents (int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_text_get_mime_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client_conflict_tree_get_details (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_tree_get_victim_node_kind (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cmdline__edit_file_externally (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 char* svn_err_best_message (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 scalar_t__ svn_mime_type_is_binary (char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

svn_error_t *
svn_cl__resolve_conflict(svn_boolean_t *quit,
                         svn_boolean_t *external_failed,
                         svn_boolean_t *printed_summary,
                         svn_client_conflict_t *conflict,
                         svn_cl__accept_t accept_which,
                         const char *editor_cmd,
                         const char *path_prefix,
                         svn_cmdline_prompt_baton_t *pb,
                         svn_cl__conflict_stats_t *conflict_stats,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *scratch_pool)
{
  svn_boolean_t text_conflicted;
  apr_array_header_t *props_conflicted;
  svn_boolean_t tree_conflicted;
  const char *local_abspath;
  svn_client_conflict_option_id_t option_id;

  SVN_ERR(svn_client_conflict_get_conflicted(&text_conflicted,
                                             &props_conflicted,
                                             &tree_conflicted,
                                             conflict,
                                             scratch_pool,
                                             scratch_pool));
  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  if (accept_which == svn_cl__accept_unspecified)
    {
      option_id = svn_client_conflict_option_unspecified;
    }
  else if (accept_which == svn_cl__accept_postpone)
    {
      option_id = svn_client_conflict_option_postpone;
    }
  else if (accept_which == svn_cl__accept_base)
    {
      option_id = svn_client_conflict_option_base_text;
    }
  else if (accept_which == svn_cl__accept_working)
    {
      option_id = svn_client_conflict_option_merged_text;

      if (text_conflicted)
        {
          const char *mime_type =
            svn_client_conflict_text_get_mime_type(conflict);

          /* There is no merged text for binary conflicts, behave as
           * if 'mine-full' was chosen. */
          if (mime_type && svn_mime_type_is_binary(mime_type))
            option_id = svn_client_conflict_option_working_text;
        }
      else if (tree_conflicted)
        {
          /* For tree conflicts, map 'working' to 'accept current working
           * copy state'. */
          option_id = svn_client_conflict_option_accept_current_wc_state;
        }
    }
  else if (accept_which == svn_cl__accept_theirs_conflict)
    {
      option_id = svn_client_conflict_option_incoming_text_where_conflicted;
    }
  else if (accept_which == svn_cl__accept_mine_conflict)
    {
      option_id = svn_client_conflict_option_working_text_where_conflicted;

      if (tree_conflicted)
        {
          svn_wc_operation_t operation;

          operation = svn_client_conflict_get_operation(conflict);
          if (operation == svn_wc_operation_update ||
              operation == svn_wc_operation_switch)
            {
              svn_wc_conflict_reason_t reason;

              reason = svn_client_conflict_get_local_change(conflict);
              if (reason == svn_wc_conflict_reason_moved_away)
                {
                  /* Map 'mine-conflict' to 'update move destination'. */
                  option_id =
                    svn_client_conflict_option_update_move_destination;
                }
              else if (reason == svn_wc_conflict_reason_deleted ||
                       reason == svn_wc_conflict_reason_replaced)
                {
                  svn_wc_conflict_action_t action;
                  svn_node_kind_t node_kind;

                  action = svn_client_conflict_get_incoming_change(conflict);
                  node_kind =
                    svn_client_conflict_tree_get_victim_node_kind(conflict);

                  if (action == svn_wc_conflict_action_edit &&
                      node_kind == svn_node_dir)
                    {
                      /* Map 'mine-conflict' to 'update any moved away
                       * children'. */
                      option_id =
                        svn_client_conflict_option_update_any_moved_away_children;
                    }
                }
            }
        }
    }
  else if (accept_which == svn_cl__accept_theirs_full)
    {
      option_id = svn_client_conflict_option_incoming_text;
    }
  else if (accept_which == svn_cl__accept_mine_full)
    {
      option_id = svn_client_conflict_option_working_text;
    }
  else if (accept_which == svn_cl__accept_edit)
    {
      option_id = svn_client_conflict_option_unspecified;

      if (local_abspath)
        {
          if (*external_failed)
            {
              option_id = svn_client_conflict_option_postpone;
            }
          else
            {
              svn_error_t *err;

              err = svn_cmdline__edit_file_externally(local_abspath,
                                                      editor_cmd,
                                                      ctx->config,
                                                      scratch_pool);
              if (err && (err->apr_err == SVN_ERR_CL_NO_EXTERNAL_EDITOR ||
                          err->apr_err == SVN_ERR_EXTERNAL_PROGRAM))
                {
                  char buf[1024];
                  const char *message;

                  message = svn_err_best_message(err, buf, sizeof(buf));
                  SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "%s\n",
                                              message));
                  svn_error_clear(err);
                  *external_failed = TRUE;
                }
              else if (err)
                return svn_error_trace(err);
              option_id = svn_client_conflict_option_merged_text;
            }
        }
    }
  else if (accept_which == svn_cl__accept_launch)
    {
      const char *base_abspath = NULL;
      const char *my_abspath = NULL;
      const char *their_abspath = NULL;

      option_id = svn_client_conflict_option_unspecified;

      if (text_conflicted)
        SVN_ERR(svn_client_conflict_text_get_contents(NULL, &my_abspath,
                                                      &base_abspath,
                                                      &their_abspath,
                                                      conflict, scratch_pool,
                                                      scratch_pool));

      if (base_abspath && their_abspath && my_abspath && local_abspath)
        {
          if (*external_failed)
            {
              option_id = svn_client_conflict_option_postpone;
            }
          else
            {
              svn_boolean_t remains_in_conflict;
              svn_error_t *err;

              err = svn_cl__merge_file_externally(base_abspath, their_abspath,
                                                  my_abspath, local_abspath,
                                                  local_abspath, ctx->config,
                                                  &remains_in_conflict,
                                                  scratch_pool);
              if (err && (err->apr_err == SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL ||
                          err->apr_err == SVN_ERR_EXTERNAL_PROGRAM))
                {
                  char buf[1024];
                  const char *message;

                  message = svn_err_best_message(err, buf, sizeof(buf));
                  SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "%s\n",
                                              message));
                  *external_failed = TRUE;
                  return svn_error_trace(err);
                }
              else if (err)
                return svn_error_trace(err);

              if (remains_in_conflict)
                option_id = svn_client_conflict_option_postpone;
              else
                option_id = svn_client_conflict_option_merged_text;
            }
        }
    }
  else if (accept_which == svn_cl__accept_recommended)
    {
      svn_client_conflict_option_id_t recommended_id;

      if (tree_conflicted)
        SVN_ERR(svn_client_conflict_tree_get_details(conflict, ctx,
                                                     scratch_pool));
      recommended_id = svn_client_conflict_get_recommended_option_id(conflict);
      if (recommended_id != svn_client_conflict_option_unspecified)
        option_id = recommended_id;
      else
        option_id = svn_client_conflict_option_postpone;
    }
  else
    SVN_ERR_MALFUNCTION();

  /* If we are in interactive mode and either the user gave no --accept
   * option or the option did not apply, then prompt. */
  if (option_id == svn_client_conflict_option_unspecified)
    {
      svn_boolean_t resolved = FALSE;
      svn_boolean_t postponed = FALSE;
      svn_boolean_t printed_description = FALSE;
      svn_error_t *err;

      *quit = FALSE;

      while (!resolved && !postponed && !*quit)
        {
          err = resolve_conflict_interactively(&resolved, &postponed, quit,
                                               external_failed,
                                               printed_summary,
                                               &printed_description,
                                               conflict,
                                               editor_cmd, ctx->config,
                                               path_prefix, pb,
                                               conflict_stats, ctx,
                                               scratch_pool, scratch_pool);
          if (err && err->apr_err == SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE)
            {
              /* Conflict resolution has failed. Let the user try again.
               * It is always possible to break out of this loop with
               * the 'quit' or 'postpone' options. */
              svn_handle_warning2(stderr, err, "svn: ");
              svn_error_clear(err);
              err = SVN_NO_ERROR;
            }
          SVN_ERR(err);
        }
    }
  else if (option_id != svn_client_conflict_option_postpone)
    SVN_ERR(mark_conflict_resolved(conflict, option_id,
                                   text_conflicted,
                                   props_conflicted->nelts > 0 ? "" : NULL,
                                   tree_conflicted,
                                   path_prefix, conflict_stats,
                                   ctx, scratch_pool));

  return SVN_NO_ERROR;
}