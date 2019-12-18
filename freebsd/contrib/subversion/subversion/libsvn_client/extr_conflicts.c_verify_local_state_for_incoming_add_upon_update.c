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
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_12__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  char const* svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 char const* svn_client_conflict_option_incoming_add_ignore ; 
 char const* svn_client_conflict_option_incoming_added_dir_replace ; 
 char* svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_node_kind_to_word (scalar_t__) ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_get_base (scalar_t__*,scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_is_added (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
verify_local_state_for_incoming_add_upon_update(
  svn_client_conflict_t *conflict,
  svn_client_conflict_option_t *option,
  svn_client_ctx_t *ctx,
  apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  svn_client_conflict_option_id_t option_id;
  const char *wcroot_abspath;
  svn_wc_operation_t operation;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  svn_node_kind_t incoming_new_kind;
  const char *base_repos_relpath;
  svn_revnum_t base_rev;
  svn_node_kind_t base_kind;
  const char *local_style_relpath;
  svn_boolean_t is_added;
  svn_error_t *err;

  local_abspath = svn_client_conflict_get_local_abspath(conflict);
  option_id = svn_client_conflict_option_get_id(option);
  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, ctx->wc_ctx,
                             local_abspath, scratch_pool,
                             scratch_pool));
  operation = svn_client_conflict_get_operation(conflict);
  SVN_ERR_ASSERT(operation == svn_wc_operation_update);

  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            &incoming_new_kind, conflict, scratch_pool,
            scratch_pool));

  local_style_relpath = svn_dirent_local_style(
                          svn_dirent_skip_ancestor(wcroot_abspath,
                                                   local_abspath),
                          scratch_pool);

  /* Check if a local addition addition replaces the incoming new node. */
  err = svn_wc__node_get_base(&base_kind, &base_rev, &base_repos_relpath,
                              NULL, NULL, NULL, ctx->wc_ctx, local_abspath,
                              FALSE, scratch_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
    {
      if (option_id == svn_client_conflict_option_incoming_add_ignore)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, err,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected a base node but found none)"),
                                 local_style_relpath);
      else if (option_id ==
               svn_client_conflict_option_incoming_added_dir_replace)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, err,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected a base node but found none)"),
                                 local_style_relpath);
      else
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, err,
                                 _("Unexpected option id '%d'"), option_id);
    }
  else if (err)
    return svn_error_trace(err);

  if (base_kind != incoming_new_kind)
    {
      if (option_id == svn_client_conflict_option_incoming_add_ignore)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected base node kind '%s', "
                                   "but found '%s')"),
                                 local_style_relpath,
                                 svn_node_kind_to_word(incoming_new_kind),
                                 svn_node_kind_to_word(base_kind));
      else if (option_id ==
               svn_client_conflict_option_incoming_added_dir_replace)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected base node kind '%s', "
                                   "but found '%s')"),
                                  local_style_relpath,
                                 svn_node_kind_to_word(incoming_new_kind),
                                 svn_node_kind_to_word(base_kind));
      else
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Unexpected option id '%d'"), option_id);
    }

  if (strcmp(base_repos_relpath, incoming_new_repos_relpath) != 0 ||
      base_rev != incoming_new_pegrev)
    {
      if (option_id == svn_client_conflict_option_incoming_add_ignore)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected base node from '^/%s@%ld', "
                                   "but found '^/%s@%ld')"),
                                 local_style_relpath,
                                 incoming_new_repos_relpath,
                                 incoming_new_pegrev,
                                 base_repos_relpath, base_rev);
      else if (option_id ==
               svn_client_conflict_option_incoming_added_dir_replace)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected base node from '^/%s@%ld', "
                                   "but found '^/%s@%ld')"),
                                 local_style_relpath,
                                 incoming_new_repos_relpath,
                                 incoming_new_pegrev,
                                 base_repos_relpath, base_rev);
      else
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Unexpected option id '%d'"), option_id);
    }

  SVN_ERR(svn_wc__node_is_added(&is_added, ctx->wc_ctx, local_abspath,
                                scratch_pool));
  if (!is_added)
    {
      if (option_id == svn_client_conflict_option_incoming_add_ignore)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected an added item, but the item "
                                   "is not added)"),
                                 local_style_relpath);

      else if (option_id ==
               svn_client_conflict_option_incoming_added_dir_replace)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Cannot resolve tree conflict on '%s' "
                                   "(expected an added item, but the item "
                                   "is not added)"),
                                 local_style_relpath);
      else
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Unexpected option id '%d'"), option_id);
    }

  return SVN_NO_ERROR;
}