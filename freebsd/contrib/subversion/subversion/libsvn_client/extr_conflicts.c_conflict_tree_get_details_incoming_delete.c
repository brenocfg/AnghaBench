#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_18__ {struct conflict_tree_incoming_delete_details* tree_conflict_incoming_details; int /*<<< orphan*/  pool; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
struct conflict_tree_incoming_delete_details {char const* rev_author; int /*<<< orphan*/ * moves; scalar_t__ replacing_node_kind; void* repos_relpath; scalar_t__ added_rev; scalar_t__ deleted_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct conflict_tree_incoming_delete_details* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  find_related_node (char const**,scalar_t__*,char const*,scalar_t__,char const*,scalar_t__,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_revision_for_suspected_deletion (scalar_t__*,char const**,scalar_t__*,int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,char const*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_incoming_delete_details_for_reverse_addition (struct conflict_tree_incoming_delete_details**,char const*,char const*,scalar_t__,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_wc_move_targets (struct conflict_tree_incoming_delete_details*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,scalar_t__*,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,scalar_t__*,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_local_abspath (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_repos_info (scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
conflict_tree_get_details_incoming_delete(svn_client_conflict_t *conflict,
                                          svn_client_ctx_t *ctx,
                                          apr_pool_t *scratch_pool)
{
  const char *old_repos_relpath;
  const char *new_repos_relpath;
  const char *repos_root_url;
  svn_revnum_t old_rev;
  svn_revnum_t new_rev;
  svn_node_kind_t old_kind;
  svn_node_kind_t new_kind;
  struct conflict_tree_incoming_delete_details *details;
  svn_wc_operation_t operation;

  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &old_repos_relpath, &old_rev, &old_kind, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &new_repos_relpath, &new_rev, &new_kind, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL,
                                             conflict,
                                             scratch_pool, scratch_pool));
  operation = svn_client_conflict_get_operation(conflict);

  if (operation == svn_wc_operation_update)
    {
      if (old_rev < new_rev)
        {
          const char *parent_repos_relpath;
          svn_revnum_t parent_peg_rev;
          svn_revnum_t deleted_rev;
          const char *deleted_rev_author;
          svn_node_kind_t replacing_node_kind;
          apr_array_header_t *moves;
          const char *related_repos_relpath;
          svn_revnum_t related_peg_rev;

          /* The update operation went forward in history. */
          SVN_ERR(svn_wc__node_get_repos_info(&parent_peg_rev,
                                              &parent_repos_relpath,
                                              NULL, NULL,
                                              ctx->wc_ctx,
                                              svn_dirent_dirname(
                                                conflict->local_abspath,
                                                scratch_pool),
                                              scratch_pool,
                                              scratch_pool));
          if (new_kind == svn_node_none)
            {
              SVN_ERR(find_related_node(&related_repos_relpath,
                                        &related_peg_rev,
                                        new_repos_relpath, new_rev,
                                        old_repos_relpath, old_rev,
                                        conflict, ctx,
                                        scratch_pool, scratch_pool));
            }
          else
            {
              /* related to self */
              related_repos_relpath = NULL;
              related_peg_rev = SVN_INVALID_REVNUM;
            }

          SVN_ERR(find_revision_for_suspected_deletion(
                    &deleted_rev, &deleted_rev_author, &replacing_node_kind,
                    &moves, conflict,
                    svn_dirent_basename(conflict->local_abspath, scratch_pool),
                    parent_repos_relpath, parent_peg_rev,
                    new_kind == svn_node_none ? 0 : old_rev,
                    related_repos_relpath, related_peg_rev,
                    ctx, conflict->pool, scratch_pool));
          if (deleted_rev == SVN_INVALID_REVNUM)
            {
              /* We could not determine the revision in which the node was
               * deleted. We cannot provide the required details so the best
               * we can do is fall back to the default description. */
              return SVN_NO_ERROR;
            }

          details = apr_pcalloc(conflict->pool, sizeof(*details));
          details->deleted_rev = deleted_rev;
          details->added_rev = SVN_INVALID_REVNUM;
          details->repos_relpath = apr_pstrdup(conflict->pool,
                                               new_repos_relpath);
          details->rev_author = deleted_rev_author;
          details->replacing_node_kind = replacing_node_kind;
          details->moves = moves;
        }
      else /* new_rev < old_rev */
        {
          /* The update operation went backwards in history.
           * Figure out when this node was added. */
          SVN_ERR(get_incoming_delete_details_for_reverse_addition(
                    &details, repos_root_url, old_repos_relpath,
                    old_rev, new_rev, ctx,
                    svn_client_conflict_get_local_abspath(conflict),
                    conflict->pool, scratch_pool));
        }
    }
  else if (operation == svn_wc_operation_switch ||
           operation == svn_wc_operation_merge)
    {
      if (old_rev < new_rev)
        {
          svn_revnum_t deleted_rev;
          const char *deleted_rev_author;
          svn_node_kind_t replacing_node_kind;
          apr_array_header_t *moves;

          /* The switch/merge operation went forward in history.
           *
           * The deletion of the node happened on the branch we switched to
           * or merged from. Scan new_repos_relpath's parent's log to find
           * the revision which deleted the node. */
          SVN_ERR(find_revision_for_suspected_deletion(
                    &deleted_rev, &deleted_rev_author, &replacing_node_kind,
                    &moves, conflict,
                    svn_relpath_basename(new_repos_relpath, scratch_pool),
                    svn_relpath_dirname(new_repos_relpath, scratch_pool),
                    new_rev, old_rev, old_repos_relpath, old_rev, ctx,
                    conflict->pool, scratch_pool));
          if (deleted_rev == SVN_INVALID_REVNUM)
            {
              /* We could not determine the revision in which the node was
               * deleted. We cannot provide the required details so the best
               * we can do is fall back to the default description. */
              return SVN_NO_ERROR;
            }

          details = apr_pcalloc(conflict->pool, sizeof(*details));
          details->deleted_rev = deleted_rev;
          details->added_rev = SVN_INVALID_REVNUM;
          details->repos_relpath = apr_pstrdup(conflict->pool,
                                               new_repos_relpath);
          details->rev_author = apr_pstrdup(conflict->pool,
                                            deleted_rev_author);
          details->replacing_node_kind = replacing_node_kind;
          details->moves = moves;
        }
      else /* new_rev < old_rev */
        {
          /* The switch/merge operation went backwards in history.
           * Figure out when the node we switched away from, or merged
           * from another branch, was added. */
          SVN_ERR(get_incoming_delete_details_for_reverse_addition(
                    &details, repos_root_url, old_repos_relpath,
                    old_rev, new_rev, ctx,
                    svn_client_conflict_get_local_abspath(conflict),
                    conflict->pool, scratch_pool));
        }
    }
  else
    {
      details = NULL;
    }

  conflict->tree_conflict_incoming_details = details;

  if (details && details->moves)
    SVN_ERR(init_wc_move_targets(details, conflict, ctx, scratch_pool));

  return SVN_NO_ERROR;
}