#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_22__ {int /*<<< orphan*/  number; } ;
struct TYPE_24__ {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  TYPE_4__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_25__ {struct notification_adjust_baton* notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_5__ svn_client_ctx_t ;
struct TYPE_26__ {int /*<<< orphan*/  resolution_tree; } ;
typedef  TYPE_6__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  scalar_t__ svn_boolean_t ;
struct notification_adjust_baton {char const* checkout_abspath; char const* final_abspath; struct notification_adjust_baton* inner_baton; int /*<<< orphan*/  (* inner_func ) (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct find_added_rev_baton {char const* victim_abspath; scalar_t__ added_rev; int /*<<< orphan*/ * pool; int /*<<< orphan*/  parent_repos_relpath; int /*<<< orphan*/ * repos_relpath; TYPE_5__* ctx; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  find_added_rev ; 
 int /*<<< orphan*/ * merge_newly_added_dir (char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notification_adjust_func (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rev_below (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__checkout_internal (int /*<<< orphan*/ *,scalar_t__*,char const*,char const*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_6__*) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/ * svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_opt_revision_number ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_location_segments (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct find_added_rev_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock_for_resolve (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__del_tree_conflict (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__get_tmpdir (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__node_get_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__release_write_lock (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_copy3 (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_delete4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct notification_adjust_baton*,TYPE_2__*,int /*<<< orphan*/ *),struct notification_adjust_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_add ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_tree ; 
 int /*<<< orphan*/ * svn_wc_remove_from_revision_control2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
merge_incoming_added_dir_replace(svn_client_conflict_option_t *option,
                                 svn_client_conflict_t *conflict,
                                 svn_client_ctx_t *ctx,
                                 svn_boolean_t merge_dirs,
                                 apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  const char *url;
  const char *corrected_url;
  const char *repos_root_url;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  const char *local_abspath;
  const char *lock_abspath;
  const char *tmpdir_abspath, *tmp_abspath;
  svn_error_t *err;
  svn_revnum_t copy_src_revnum;
  svn_opt_revision_t copy_src_peg_revision;
  svn_boolean_t timestamp_sleep;
  svn_wc_notify_func2_t old_notify_func2 = ctx->notify_func2;
  void *old_notify_baton2 = ctx->notify_baton2;
  struct notification_adjust_baton nb;

  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  /* Find the URL of the incoming added directory in the repository. */
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            NULL, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL,
                                             conflict, scratch_pool,
                                             scratch_pool));
  url = svn_path_url_add_component2(repos_root_url, incoming_new_repos_relpath,
                                    scratch_pool);
  SVN_ERR(svn_client__open_ra_session_internal(&ra_session, &corrected_url,
                                               url, NULL, NULL, FALSE, FALSE,
                                               ctx, scratch_pool,
                                               scratch_pool));
  if (corrected_url)
    url = corrected_url;


  /* Find a temporary location in which to check out the copy source. */
  SVN_ERR(svn_wc__get_tmpdir(&tmpdir_abspath, ctx->wc_ctx, local_abspath,
                             scratch_pool, scratch_pool));

  SVN_ERR(svn_io_open_unique_file3(NULL, &tmp_abspath, tmpdir_abspath,
                                   svn_io_file_del_on_close,
                                   scratch_pool, scratch_pool));

  /* Make a new checkout of the requested source. While doing so,
   * resolve copy_src_revnum to an actual revision number in case it
   * was until now 'invalid' meaning 'head'.  Ask this function not to
   * sleep for timestamps, by passing a sleep_needed output param.
   * Send notifications for all nodes except the root node, and adjust
   * them to refer to the destination rather than this temporary path. */

  nb.inner_func = ctx->notify_func2;
  nb.inner_baton = ctx->notify_baton2;
  nb.checkout_abspath = tmp_abspath;
  nb.final_abspath = local_abspath;
  ctx->notify_func2 = notification_adjust_func;
  ctx->notify_baton2 = &nb;

  copy_src_peg_revision.kind = svn_opt_revision_number;
  copy_src_peg_revision.value.number = incoming_new_pegrev;

  err = svn_client__checkout_internal(&copy_src_revnum, &timestamp_sleep,
                                      url, tmp_abspath,
                                      &copy_src_peg_revision,
                                      &copy_src_peg_revision,
                                      svn_depth_infinity,
                                      TRUE, /* we want to ignore externals */
                                      FALSE, /* we don't allow obstructions */
                                      ra_session, ctx, scratch_pool);

  ctx->notify_func2 = old_notify_func2;
  ctx->notify_baton2 = old_notify_baton2;

  SVN_ERR(err);

  /* ### The following WC modifications should be atomic. */

  SVN_ERR(svn_wc__acquire_write_lock_for_resolve(&lock_abspath, ctx->wc_ctx,
                                                 svn_dirent_dirname(
                                                   local_abspath,
                                                   scratch_pool),
                                                 scratch_pool, scratch_pool));

  /* Remove the working directory. */
  err = svn_wc_delete4(ctx->wc_ctx, local_abspath, FALSE, FALSE,
                       NULL, NULL, /* don't allow user to cancel here */
                       ctx->notify_func2, ctx->notify_baton2,
                       scratch_pool);
  if (err)
    goto unlock_wc;

  /* Schedule dst_path for addition in parent, with copy history.
     Don't send any notification here.
     Then remove the temporary checkout's .svn dir in preparation for
     moving the rest of it into the final destination. */
  err = svn_wc_copy3(ctx->wc_ctx, tmp_abspath, local_abspath,
                     TRUE /* metadata_only */,
                     NULL, NULL, /* don't allow user to cancel here */
                     NULL, NULL, scratch_pool);
  if (err)
    goto unlock_wc;

  err = svn_wc__acquire_write_lock(NULL, ctx->wc_ctx, tmp_abspath,
                                   FALSE, scratch_pool, scratch_pool);
  if (err)
    goto unlock_wc;
  err = svn_wc_remove_from_revision_control2(ctx->wc_ctx,
                                             tmp_abspath,
                                             FALSE, FALSE,
                                             NULL, NULL, /* don't cancel */
                                             scratch_pool);
  if (err)
    goto unlock_wc;

  /* Move the temporary disk tree into place. */
  err = svn_io_file_rename2(tmp_abspath, local_abspath, FALSE, scratch_pool);
  if (err)
    goto unlock_wc;

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(local_abspath,
                                                     svn_wc_notify_add,
                                                     scratch_pool);
      notify->kind = svn_node_dir;
      ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
    }

  /* Resolve to current working copy state.
   * svn_client__merge_locked() requires this. */
  err = svn_wc__del_tree_conflict(ctx->wc_ctx, local_abspath, scratch_pool);
  if (err)
    goto unlock_wc;

  if (merge_dirs)
    {
      svn_revnum_t base_revision;
      const char *base_repos_relpath;
      struct find_added_rev_baton b = { 0 };

      /* Find the URL and revision of the directory we have just replaced. */
      err = svn_wc__node_get_base(NULL, &base_revision, &base_repos_relpath,
                                  NULL, NULL, NULL, ctx->wc_ctx, local_abspath,
                                  FALSE, scratch_pool, scratch_pool);
      if (err)
        goto unlock_wc;

      url = svn_path_url_add_component2(repos_root_url, base_repos_relpath,
                                        scratch_pool);

      /* Trace the replaced directory's history to its origin. */
      err = svn_ra_reparent(ra_session, url, scratch_pool);
      if (err)
        goto unlock_wc;
      b.victim_abspath = local_abspath;
      b.ctx = ctx;
      b.added_rev = SVN_INVALID_REVNUM;
      b.repos_relpath = NULL;
      b.parent_repos_relpath = svn_relpath_dirname(base_repos_relpath,
                                                   scratch_pool);
      b.pool = scratch_pool;

      err = svn_ra_get_location_segments(ra_session, "", base_revision,
                                         base_revision, SVN_INVALID_REVNUM,
                                         find_added_rev, &b,
                                         scratch_pool);
      if (err)
        goto unlock_wc;

      if (b.added_rev == SVN_INVALID_REVNUM)
        {
          err = svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                                  _("Could not determine the revision in "
                                    "which '^/%s' was added to the "
                                    "repository.\n"),
                                  base_repos_relpath);
          goto unlock_wc;
        }

      /* Merge the replaced directory into the directory which replaced it.
       * We do not need to consider a reverse-merge here since the source of
       * this merge was part of the merge target working copy, not a branch
       * in the repository. */
      err = merge_newly_added_dir(base_repos_relpath,
                                  url, rev_below(b.added_rev), url,
                                  base_revision, local_abspath, FALSE,
                                  ctx, scratch_pool, scratch_pool);
      if (err)
        goto unlock_wc;
    }

unlock_wc:
  err = svn_error_compose_create(err, svn_wc__release_write_lock(ctx->wc_ctx,
                                                                 lock_abspath,
                                                                 scratch_pool));
  svn_io_sleep_for_timestamps(local_abspath, scratch_pool);
  SVN_ERR(err);

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(
                                  local_abspath,
                                  svn_wc_notify_resolved_tree,
                                  scratch_pool);

      ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
    }

  conflict->resolution_tree = svn_client_conflict_option_get_id(option);

  return SVN_NO_ERROR;
}