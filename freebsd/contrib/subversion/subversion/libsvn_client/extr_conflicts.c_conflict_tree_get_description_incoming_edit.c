#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/ * tree_conflict_incoming_details; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,scalar_t__,...) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  conflict_tree_get_incoming_description_generic (char const**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ describe_incoming_edit_list_modified_revs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* describe_incoming_edit_upon_switch (char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 char* describe_incoming_edit_upon_update (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,scalar_t__*,scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,scalar_t__*,scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
conflict_tree_get_description_incoming_edit(
  const char **incoming_change_description,
  svn_client_conflict_t *conflict,
  svn_client_ctx_t *ctx,
  apr_pool_t *result_pool,
  apr_pool_t *scratch_pool)
{
  const char *action;
  svn_wc_operation_t conflict_operation;
  const char *old_repos_relpath;
  svn_revnum_t old_rev;
  svn_node_kind_t old_node_kind;
  const char *new_repos_relpath;
  svn_revnum_t new_rev;
  svn_node_kind_t new_node_kind;
  apr_array_header_t *edits;

  if (conflict->tree_conflict_incoming_details == NULL)
    return svn_error_trace(conflict_tree_get_incoming_description_generic(
                             incoming_change_description, conflict, ctx,
                             result_pool, scratch_pool));

  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &old_repos_relpath, &old_rev, &old_node_kind, conflict,
            scratch_pool, scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &new_repos_relpath, &new_rev, &new_node_kind, conflict,
            scratch_pool, scratch_pool));

  conflict_operation = svn_client_conflict_get_operation(conflict);

  edits = conflict->tree_conflict_incoming_details;

  if (conflict_operation == svn_wc_operation_update)
    action = describe_incoming_edit_upon_update(old_rev, new_rev,
                                                old_node_kind, new_node_kind,
                                                scratch_pool);
  else if (conflict_operation == svn_wc_operation_switch)
    action = describe_incoming_edit_upon_switch(new_repos_relpath, new_rev,
                                                new_node_kind, scratch_pool);
  else if (conflict_operation == svn_wc_operation_merge)
    {
      /* Handle merge inline because it returns early sometimes. */
      if (old_rev < new_rev)
        {
          if (old_rev + 1 == new_rev)
            {
              if (new_node_kind == svn_node_dir)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a directory "
                                        "arrived during merge of\n"
                                        "'^/%s:%ld'."),
                                        new_repos_relpath, new_rev);
              else if (new_node_kind == svn_node_file ||
                       new_node_kind == svn_node_symlink)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a file "
                                        "arrived during merge of\n"
                                        "'^/%s:%ld'."),
                                      new_repos_relpath, new_rev);
              else
                action = apr_psprintf(scratch_pool,
                                      _("Changes arrived during merge of\n"
                                        "'^/%s:%ld'."),
                                      new_repos_relpath, new_rev);

              *incoming_change_description = apr_pstrdup(result_pool, action);

              return SVN_NO_ERROR;
            }
          else
            {
              if (new_node_kind == svn_node_dir)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a directory "
                                        "arrived via the following revisions "
                                        "during merge of\n'^/%s:%ld-%ld'"),
                                      new_repos_relpath, old_rev + 1, new_rev);
              else if (new_node_kind == svn_node_file ||
                       new_node_kind == svn_node_symlink)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a file "
                                        "arrived via the following revisions "
                                        "during merge of\n'^/%s:%ld-%ld'"),
                                      new_repos_relpath, old_rev + 1, new_rev);
              else
                action = apr_psprintf(scratch_pool,
                                      _("Changes from the following revisions "
                                        "arrived during merge of\n"
                                        "'^/%s:%ld-%ld'"),
                                      new_repos_relpath, old_rev + 1, new_rev);
            }
        }
      else
        {
          if (new_rev + 1 == old_rev)
            {
              if (new_node_kind == svn_node_dir)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a directory "
                                        "arrived during reverse-merge of\n"
                                        "'^/%s:%ld'."),
                                      new_repos_relpath, old_rev);
              else if (new_node_kind == svn_node_file ||
                       new_node_kind == svn_node_symlink)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a file "
                                        "arrived during reverse-merge of\n"
                                        "'^/%s:%ld'."),
                                      new_repos_relpath, old_rev);
              else
                action = apr_psprintf(scratch_pool,
                                      _("Changes arrived during reverse-merge "
                                        "of\n'^/%s:%ld'."),
                                      new_repos_relpath, old_rev);

              *incoming_change_description = apr_pstrdup(result_pool, action);

              return SVN_NO_ERROR;
            }
          else
            {
              if (new_node_kind == svn_node_dir)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a directory "
                                        "arrived via the following revisions "
                                        "during reverse-merge of\n"
                                        "'^/%s:%ld-%ld'"),
                                      new_repos_relpath, new_rev + 1, old_rev);
              else if (new_node_kind == svn_node_file ||
                       new_node_kind == svn_node_symlink)
                action = apr_psprintf(scratch_pool,
                                      _("Changes destined for a file "
                                        "arrived via the following revisions "
                                        "during reverse-merge of\n"
                                        "'^/%s:%ld-%ld'"),
                                      new_repos_relpath, new_rev + 1, old_rev);
                
              else
                action = apr_psprintf(scratch_pool,
                                      _("Changes from the following revisions "
                                        "arrived during reverse-merge of\n"
                                        "'^/%s:%ld-%ld'"),
                                      new_repos_relpath, new_rev + 1, old_rev);
            }
        }
    }

  action = apr_psprintf(scratch_pool, "%s:\n%s", action,
                        describe_incoming_edit_list_modified_revs(
                          edits, scratch_pool));
  *incoming_change_description = apr_pstrdup(result_pool, action);

  return SVN_NO_ERROR;
}