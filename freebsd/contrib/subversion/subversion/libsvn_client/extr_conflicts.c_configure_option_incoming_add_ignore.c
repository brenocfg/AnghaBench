#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_incoming_add_ignore ; 
 scalar_t__ svn_client_conflict_get_incoming_change (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_add_ignore ; 
 scalar_t__ svn_client_conflict_tree_get_victim_node_kind (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_add ; 
 scalar_t__ svn_wc_conflict_reason_added ; 
 scalar_t__ svn_wc_conflict_reason_obstructed ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
configure_option_incoming_add_ignore(svn_client_conflict_t *conflict,
                                     svn_client_ctx_t *ctx,
                                     apr_array_header_t *options,
                                     apr_pool_t *scratch_pool)
{
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t incoming_change;
  svn_wc_conflict_reason_t local_change;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  svn_node_kind_t victim_node_kind;

  operation = svn_client_conflict_get_operation(conflict);
  incoming_change = svn_client_conflict_get_incoming_change(conflict);
  local_change = svn_client_conflict_get_local_change(conflict);
  victim_node_kind = svn_client_conflict_tree_get_victim_node_kind(conflict);
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            NULL, conflict, scratch_pool,
            scratch_pool));

  /* This option is only available for directories. */
  if (victim_node_kind == svn_node_dir &&
      incoming_change == svn_wc_conflict_action_add &&
      (local_change == svn_wc_conflict_reason_obstructed ||
       local_change == svn_wc_conflict_reason_added))
    {
      const char *description;
      const char *wcroot_abspath;

      SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, ctx->wc_ctx,
                                 conflict->local_abspath, scratch_pool,
                                 scratch_pool));
      if (operation == svn_wc_operation_merge)
        description =
          apr_psprintf(scratch_pool,
                       _("ignore and do not add '^/%s@%ld' here"),
                       incoming_new_repos_relpath, incoming_new_pegrev);
      else if (operation == svn_wc_operation_update ||
               operation == svn_wc_operation_switch)
        {
          if (victim_node_kind == svn_node_file)
            description =
              apr_psprintf(scratch_pool,
                           _("replace '^/%s@%ld' with the locally added file"),
                           incoming_new_repos_relpath, incoming_new_pegrev);
          else if (victim_node_kind == svn_node_dir)
            description =
              apr_psprintf(scratch_pool,
                           _("replace '^/%s@%ld' with the locally added "
                             "directory"),
                           incoming_new_repos_relpath, incoming_new_pegrev);
          else
            description =
              apr_psprintf(scratch_pool,
                           _("replace '^/%s@%ld' with the locally added item"),
                           incoming_new_repos_relpath, incoming_new_pegrev);
        }
      else
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("unexpected operation code '%d'"),
                                 operation);
      add_resolution_option(
        options, conflict, svn_client_conflict_option_incoming_add_ignore,
        _("Ignore incoming addition"), description, resolve_incoming_add_ignore);
    }

  return SVN_NO_ERROR;
}