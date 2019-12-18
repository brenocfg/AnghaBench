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
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_abspath; struct conflict_tree_incoming_delete_details* tree_conflict_incoming_details; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct conflict_tree_incoming_delete_details {scalar_t__ deleted_rev; scalar_t__ added_rev; char const* repos_relpath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_tree_get_victim_node_kind (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_skip_ancestor (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_kind_to_word (scalar_t__) ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int /*<<< orphan*/ *,scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
verify_local_state_for_incoming_delete(svn_client_conflict_t *conflict,
                                       svn_client_conflict_option_t *option,
                                        svn_client_ctx_t *ctx,
                                       apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  const char *wcroot_abspath;
  svn_wc_operation_t operation;

  local_abspath = svn_client_conflict_get_local_abspath(conflict);
  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, ctx->wc_ctx,
                             local_abspath, scratch_pool,
                             scratch_pool));
  operation = svn_client_conflict_get_operation(conflict);

  if (operation == svn_wc_operation_update ||
      operation == svn_wc_operation_switch)
    {
      struct conflict_tree_incoming_delete_details *details;
      svn_boolean_t is_copy;
      svn_revnum_t copyfrom_rev;
      const char *copyfrom_repos_relpath;

      details = conflict->tree_conflict_incoming_details;
      if (details == NULL)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Conflict resolution option '%d' requires "
                                   "details for tree conflict at '%s' to be "
                                   "fetched from the repository."),
                                option->id,
                                svn_dirent_local_style(local_abspath,
                                                       scratch_pool));

      /* Ensure that the item is a copy of itself from before it was deleted.
       * Update and switch are supposed to set this up when flagging the
       * conflict. */
      SVN_ERR(svn_wc__node_get_origin(&is_copy, &copyfrom_rev,
                                      &copyfrom_repos_relpath,
                                      NULL, NULL, NULL, NULL,
                                      ctx->wc_ctx, local_abspath, FALSE,
                                      scratch_pool, scratch_pool));
      if (!is_copy)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected a copied item, but the item "
                                   "is not a copy)"),
                                 svn_dirent_local_style(
                                   svn_dirent_skip_ancestor(
                                     wcroot_abspath,
                                     conflict->local_abspath),
                                 scratch_pool));
      else if (details->deleted_rev == SVN_INVALID_REVNUM &&
               details->added_rev == SVN_INVALID_REVNUM)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Could not find the revision in which '%s' "
                                   "was deleted from the repository"),
                                 svn_dirent_local_style(
                                   svn_dirent_skip_ancestor(
                                     wcroot_abspath,
                                     conflict->local_abspath),
                                   scratch_pool));
      else if (details->deleted_rev != SVN_INVALID_REVNUM &&
               copyfrom_rev >= details->deleted_rev)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected an item copied from a revision "
                                   "smaller than r%ld, but the item was "
                                   "copied from r%ld)"),
                                 svn_dirent_local_style(
                                   svn_dirent_skip_ancestor(
                                     wcroot_abspath, conflict->local_abspath),
                                   scratch_pool),
                                 details->deleted_rev, copyfrom_rev);

      else if (details->added_rev != SVN_INVALID_REVNUM &&
               copyfrom_rev < details->added_rev)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected an item copied from a revision "
                                   "larger than r%ld, but the item was "
                                   "copied from r%ld)"),
                                 svn_dirent_local_style(
                                   svn_dirent_skip_ancestor(
                                     wcroot_abspath, conflict->local_abspath),
                                   scratch_pool),
                                  details->added_rev, copyfrom_rev);
      else if (operation == svn_wc_operation_update)
        {
          const char *old_repos_relpath;

          SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
                    &old_repos_relpath, NULL, NULL, conflict,
                    scratch_pool, scratch_pool));
          if (strcmp(copyfrom_repos_relpath, details->repos_relpath) != 0 &&
              strcmp(copyfrom_repos_relpath, old_repos_relpath) != 0)
            return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                     _("Cannot resolve tree conflict on '%s' "
                                       "(expected an item copied from '^/%s' "
                                       "or from '^/%s' but the item was "
                                       "copied from '^/%s@%ld')"),
                                     svn_dirent_local_style(
                                       svn_dirent_skip_ancestor(
                                         wcroot_abspath, conflict->local_abspath),
                                       scratch_pool),
                                     details->repos_relpath,
                                     old_repos_relpath,
                                     copyfrom_repos_relpath, copyfrom_rev);
        }
      else if (operation == svn_wc_operation_switch)
        {
          const char *old_repos_relpath;

          SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
                    &old_repos_relpath, NULL, NULL, conflict,
                    scratch_pool, scratch_pool));

          if (strcmp(copyfrom_repos_relpath, old_repos_relpath) != 0)
            return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                     _("Cannot resolve tree conflict on '%s' "
                                       "(expected an item copied from '^/%s', "
                                       "but the item was copied from "
                                        "'^/%s@%ld')"),
                                     svn_dirent_local_style(
                                       svn_dirent_skip_ancestor(
                                         wcroot_abspath,
                                         conflict->local_abspath),
                                       scratch_pool),
                                     old_repos_relpath,
                                     copyfrom_repos_relpath, copyfrom_rev);
        }
    }
  else if (operation == svn_wc_operation_merge)
    {
      svn_node_kind_t victim_node_kind;
      svn_node_kind_t on_disk_kind;

      /* For merge, all we can do is ensure that the item still exists. */
      victim_node_kind =
        svn_client_conflict_tree_get_victim_node_kind(conflict);
      SVN_ERR(svn_io_check_path(local_abspath, &on_disk_kind, scratch_pool));

      if (victim_node_kind != on_disk_kind)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected node kind '%s' but found '%s')"),
                                 svn_dirent_local_style(
                                   svn_dirent_skip_ancestor(
                                     wcroot_abspath, conflict->local_abspath),
                                   scratch_pool),
                                 svn_node_kind_to_word(victim_node_kind),
                                 svn_node_kind_to_word(on_disk_kind));
    }

  return SVN_NO_ERROR;
}