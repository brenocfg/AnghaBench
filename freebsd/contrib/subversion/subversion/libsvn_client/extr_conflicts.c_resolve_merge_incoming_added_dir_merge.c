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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  resolution_tree; struct conflict_tree_incoming_add_details* tree_conflict_incoming_details; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ svn_client_conflict_option_t ;
struct conflict_tree_incoming_add_details {char const* repos_relpath; scalar_t__ added_rev; scalar_t__ deleted_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * merge_newly_added_dir (char const*,char const*,scalar_t__,char const*,scalar_t__,char const*,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rev_below (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_incoming_new_repos_location (char const**,scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_incoming_old_repos_location (char const**,scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_id (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock_for_resolve (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__del_tree_conflict (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__release_write_lock (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_tree ; 

__attribute__((used)) static svn_error_t *
resolve_merge_incoming_added_dir_merge(svn_client_conflict_option_t *option,
                                       svn_client_conflict_t *conflict,
                                       svn_client_ctx_t *ctx,
                                       apr_pool_t *scratch_pool)
{
  const char *repos_root_url;
  const char *incoming_old_repos_relpath;
  svn_revnum_t incoming_old_pegrev;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  const char *local_abspath;
  const char *lock_abspath;
  struct conflict_tree_incoming_add_details *details;
  const char *added_repos_relpath;
  const char *source1;
  svn_revnum_t rev1;
  const char *source2;
  svn_revnum_t rev2;
  svn_error_t *err;

  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  details = conflict->tree_conflict_incoming_details;
  if (details == NULL)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Conflict resolution option '%d' requires "
                               "details for tree conflict at '%s' to be "
                               "fetched from the repository"),
                            option->id,
                            svn_dirent_local_style(local_abspath,
                                                   scratch_pool));

  /* Set up merge sources to merge the entire incoming added directory tree. */
  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL,
                                             conflict, scratch_pool,
                                             scratch_pool));
  source1 = svn_path_url_add_component2(repos_root_url,
                                        details->repos_relpath,
                                        scratch_pool);
  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &incoming_old_repos_relpath, &incoming_old_pegrev,
            NULL, conflict, scratch_pool, scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            NULL, conflict, scratch_pool, scratch_pool));
  if (incoming_old_pegrev < incoming_new_pegrev) /* forward merge */
    {
      if (details->added_rev == SVN_INVALID_REVNUM)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Could not determine when '%s' was "
                                   "added the repository"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
      rev1 = rev_below(details->added_rev);
      source2 = svn_path_url_add_component2(repos_root_url,
                                            incoming_new_repos_relpath,
                                            scratch_pool);
      rev2 = incoming_new_pegrev;
      added_repos_relpath = incoming_new_repos_relpath;
    }
  else /* reverse-merge */
    {
      if (details->deleted_rev == SVN_INVALID_REVNUM)
        return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                 _("Could not determine when '%s' was "
                                   "deleted from the repository"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
      rev1 = details->deleted_rev;
      source2 = svn_path_url_add_component2(repos_root_url,
                                            incoming_old_repos_relpath,
                                            scratch_pool);
      rev2 = incoming_old_pegrev;
      added_repos_relpath = incoming_new_repos_relpath;
    }

  /* ### The following WC modifications should be atomic. */
  SVN_ERR(svn_wc__acquire_write_lock_for_resolve(&lock_abspath, ctx->wc_ctx,
                                                 local_abspath,
                                                 scratch_pool, scratch_pool));

  /* ### wrap in a transaction */
  err = merge_newly_added_dir(added_repos_relpath,
                              source1, rev1, source2, rev2,
                              local_abspath,
                              (incoming_old_pegrev > incoming_new_pegrev),
                              ctx, scratch_pool, scratch_pool);
  if (!err)
    err = svn_wc__del_tree_conflict(ctx->wc_ctx, local_abspath, scratch_pool);

  err = svn_error_compose_create(err, svn_wc__release_write_lock(ctx->wc_ctx,
                                                                 lock_abspath,
                                                                 scratch_pool));
  svn_io_sleep_for_timestamps(local_abspath, scratch_pool);
  SVN_ERR(err);

  if (ctx->notify_func2)
    ctx->notify_func2(ctx->notify_baton2,
                      svn_wc_create_notify(local_abspath,
                                           svn_wc_notify_resolved_tree,
                                           scratch_pool),
                      scratch_pool);

  conflict->resolution_tree = svn_client_conflict_option_get_id(option);

  return SVN_NO_ERROR;
}