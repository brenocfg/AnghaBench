#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_8__ {struct conflict_tree_incoming_delete_details* tree_conflict_incoming_details; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
struct conflict_tree_incoming_delete_details {scalar_t__ deleted_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  conflict_tree_get_incoming_description_generic (char const**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* describe_incoming_deletion_upon_merge (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* describe_incoming_deletion_upon_switch (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* describe_incoming_deletion_upon_update (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* describe_incoming_reverse_addition_upon_merge (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* describe_incoming_reverse_addition_upon_switch (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* describe_incoming_reverse_addition_upon_update (struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_client_conflict_tree_get_victim_node_kind (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
conflict_tree_get_description_incoming_delete(
  const char **incoming_change_description,
  svn_client_conflict_t *conflict,
  svn_client_ctx_t *ctx,
  apr_pool_t *result_pool,
  apr_pool_t *scratch_pool)
{
  const char *action;
  svn_node_kind_t victim_node_kind;
  svn_wc_operation_t conflict_operation;
  const char *old_repos_relpath;
  svn_revnum_t old_rev;
  const char *new_repos_relpath;
  svn_revnum_t new_rev;
  struct conflict_tree_incoming_delete_details *details;

  if (conflict->tree_conflict_incoming_details == NULL)
    return svn_error_trace(conflict_tree_get_incoming_description_generic(
                             incoming_change_description,
                             conflict, ctx, result_pool, scratch_pool));

  conflict_operation = svn_client_conflict_get_operation(conflict);
  victim_node_kind = svn_client_conflict_tree_get_victim_node_kind(conflict);
  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &old_repos_relpath, &old_rev, NULL, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &new_repos_relpath, &new_rev, NULL, conflict, scratch_pool,
            scratch_pool));

  details = conflict->tree_conflict_incoming_details;

  if (conflict_operation == svn_wc_operation_update)
    {
      if (details->deleted_rev != SVN_INVALID_REVNUM)
        {
          action = describe_incoming_deletion_upon_update(details,
                                                          victim_node_kind,
                                                          old_rev,
                                                          new_rev,
                                                          result_pool,
                                                          scratch_pool);
        }
      else /* details->added_rev != SVN_INVALID_REVNUM */
        {
          /* This deletion is really the reverse change of an addition. */
          action = describe_incoming_reverse_addition_upon_update(
                     details, victim_node_kind, old_rev, new_rev, result_pool);
        }
    }
  else if (conflict_operation == svn_wc_operation_switch)
    {
      if (details->deleted_rev != SVN_INVALID_REVNUM)
        {
          action = describe_incoming_deletion_upon_switch(details,
                                                          victim_node_kind,
                                                          old_repos_relpath,
                                                          old_rev,
                                                          new_repos_relpath,
                                                          new_rev,
                                                          result_pool,
                                                          scratch_pool);
        }
      else /* details->added_rev != SVN_INVALID_REVNUM */
        {
          /* This deletion is really the reverse change of an addition. */
          action = describe_incoming_reverse_addition_upon_switch(
                     details, victim_node_kind, old_repos_relpath, old_rev,
                     new_repos_relpath, new_rev, result_pool);
            
        }
      }
  else if (conflict_operation == svn_wc_operation_merge)
    {
      if (details->deleted_rev != SVN_INVALID_REVNUM)
        {
          action = describe_incoming_deletion_upon_merge(details,
                                                         victim_node_kind,
                                                         old_repos_relpath,
                                                         old_rev,
                                                         new_repos_relpath,
                                                         new_rev,
                                                         result_pool,
                                                         scratch_pool);
        }
      else /* details->added_rev != SVN_INVALID_REVNUM */
        {
          /* This deletion is really the reverse change of an addition. */
          action = describe_incoming_reverse_addition_upon_merge(
                     details, victim_node_kind, old_repos_relpath, old_rev,
                     new_repos_relpath, new_rev, result_pool);
        }
      }

  *incoming_change_description = apr_pstrdup(result_pool, action);

  return SVN_NO_ERROR;
}