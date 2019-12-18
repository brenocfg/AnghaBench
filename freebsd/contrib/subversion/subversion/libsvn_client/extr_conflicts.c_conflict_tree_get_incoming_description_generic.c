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
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* describe_incoming_change (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_conflict_action ; 
 scalar_t__ svn_client_conflict_get_incoming_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_kind_to_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ svn_wc_conflict_action_add ; 
 scalar_t__ svn_wc_conflict_action_delete ; 
 scalar_t__ svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_action_replace ; 

__attribute__((used)) static svn_error_t *
conflict_tree_get_incoming_description_generic(
  const char **incoming_change_description,
  svn_client_conflict_t *conflict,
  svn_client_ctx_t *ctx,
  apr_pool_t *result_pool,
  apr_pool_t *scratch_pool)
{
  const char *action;
  svn_node_kind_t incoming_kind;
  svn_wc_conflict_action_t conflict_action;
  svn_wc_operation_t conflict_operation;

  conflict_action = svn_client_conflict_get_incoming_change(conflict);
  conflict_operation = svn_client_conflict_get_operation(conflict);

  /* Determine the node kind of the incoming change. */
  incoming_kind = svn_node_unknown;
  if (conflict_action == svn_wc_conflict_action_edit ||
      conflict_action == svn_wc_conflict_action_delete)
    {
      /* Change is acting on 'src_left' version of the node. */
      SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
                NULL, NULL, &incoming_kind, conflict, scratch_pool,
                scratch_pool));
    }
  else if (conflict_action == svn_wc_conflict_action_add ||
           conflict_action == svn_wc_conflict_action_replace)
    {
      /* Change is acting on 'src_right' version of the node.
       *
       * ### For 'replace', the node kind is ambiguous. However, src_left
       * ### is NULL for replace, so we must use src_right. */
      SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
                NULL, NULL, &incoming_kind, conflict, scratch_pool,
                scratch_pool));
    }

  action = describe_incoming_change(incoming_kind, conflict_action,
                                    conflict_operation);
  if (action)
    {
      *incoming_change_description = apr_pstrdup(result_pool, action);
    }
  else
    {
      /* A catch-all message for very rare or nominally impossible cases.
         It will not be pretty, but is closer to an internal error than
         an ordinary user-facing string. */
      *incoming_change_description = apr_psprintf(result_pool,
                                       _("incoming %s %s"),
                                       svn_node_kind_to_word(incoming_kind),
                                       svn_token__to_word(map_conflict_action,
                                                          conflict_action));
    }
  return SVN_NO_ERROR;
}