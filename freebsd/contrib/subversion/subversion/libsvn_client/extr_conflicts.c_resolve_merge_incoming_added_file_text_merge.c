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
struct TYPE_13__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  scalar_t__ svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct TYPE_15__ {int /*<<< orphan*/  resolution_tree; } ;
typedef  TYPE_3__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/ * svn_io_file_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock_for_resolve (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__del_tree_conflict (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__get_tmpdir (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__release_write_lock (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_merge5 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_merge_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_tree ; 
 int /*<<< orphan*/  svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 

__attribute__((used)) static svn_error_t *
resolve_merge_incoming_added_file_text_merge(
  svn_client_conflict_option_t *option,
  svn_client_conflict_t *conflict,
  svn_client_ctx_t *ctx,
  apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  const char *url;
  const char *corrected_url;
  const char *repos_root_url;
  const char *wc_tmpdir;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  const char *local_abspath;
  const char *lock_abspath;
  svn_wc_merge_outcome_t merge_content_outcome;
  svn_wc_notify_state_t merge_props_outcome;
  apr_file_t *incoming_new_file;
  const char *incoming_new_tmp_abspath;
  const char *empty_file_abspath;
  svn_stream_t *incoming_new_stream;
  apr_hash_t *incoming_new_props;
  apr_array_header_t *propdiffs;
  svn_error_t *err;

  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  /* Set up temporary storage for the repository version of file. */
  SVN_ERR(svn_wc__get_tmpdir(&wc_tmpdir, ctx->wc_ctx, local_abspath,
                             scratch_pool, scratch_pool));
  SVN_ERR(svn_io_open_unique_file3(&incoming_new_file,
                                   &incoming_new_tmp_abspath, wc_tmpdir,
                                   svn_io_file_del_on_pool_cleanup,
                                   scratch_pool, scratch_pool));
  incoming_new_stream = svn_stream_from_aprfile2(incoming_new_file, TRUE,
                                                 scratch_pool);

  /* Fetch the incoming added file from the repository. */
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
  SVN_ERR(svn_ra_get_file(ra_session, "", incoming_new_pegrev,
                          incoming_new_stream, NULL, /* fetched_rev */
                          &incoming_new_props, scratch_pool));

  /* Flush file to disk. */
  SVN_ERR(svn_stream_close(incoming_new_stream));
  SVN_ERR(svn_io_file_flush(incoming_new_file, scratch_pool));

  filter_props(incoming_new_props, scratch_pool);

  /* Create an empty file as fake "merge-base" for the two added files.
   * The files are not ancestrally related so this is the best we can do. */
  SVN_ERR(svn_io_open_unique_file3(NULL, &empty_file_abspath, NULL,
                                   svn_io_file_del_on_pool_cleanup,
                                   scratch_pool, scratch_pool));

  /* Create a property diff which shows all props as added. */
  SVN_ERR(svn_prop_diffs(&propdiffs, incoming_new_props,
                         apr_hash_make(scratch_pool), scratch_pool));

  /* ### The following WC modifications should be atomic. */
  SVN_ERR(svn_wc__acquire_write_lock_for_resolve(&lock_abspath, ctx->wc_ctx,
                                                 local_abspath,
                                                 scratch_pool, scratch_pool));
  /* Resolve to current working copy state. svn_wc_merge5() requires this. */
  err = svn_wc__del_tree_conflict(ctx->wc_ctx, local_abspath, scratch_pool);
  if (err)
    return svn_error_compose_create(err,
                                    svn_wc__release_write_lock(ctx->wc_ctx,
                                                               lock_abspath,
                                                               scratch_pool));
  /* Perform the file merge. ### Merge into tempfile and then rename on top? */
  err = svn_wc_merge5(&merge_content_outcome, &merge_props_outcome,
                      ctx->wc_ctx, empty_file_abspath,
                      incoming_new_tmp_abspath, local_abspath,
                      NULL, NULL, NULL, /* labels */
                      NULL, NULL, /* conflict versions */
                      FALSE, /* dry run */
                      NULL, NULL, /* diff3_cmd, merge_options */
                      NULL, propdiffs,
                      NULL, NULL, /* conflict func/baton */
                      NULL, NULL, /* don't allow user to cancel here */
                      scratch_pool);
  err = svn_error_compose_create(err, svn_wc__release_write_lock(ctx->wc_ctx,
                                                                 lock_abspath,
                                                                 scratch_pool));
  svn_io_sleep_for_timestamps(local_abspath, scratch_pool);
  SVN_ERR(err);

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify;

      /* Tell the world about the file merge that just happened. */
      notify = svn_wc_create_notify(local_abspath,
                                    svn_wc_notify_update_update,
                                    scratch_pool);
      if (merge_content_outcome == svn_wc_merge_conflict)
        notify->content_state = svn_wc_notify_state_conflicted;
      else
        notify->content_state = svn_wc_notify_state_merged;
      notify->prop_state = merge_props_outcome;
      notify->kind = svn_node_file;
      ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);

      /* And also about the successfully resolved tree conflict. */
      notify = svn_wc_create_notify(local_abspath, svn_wc_notify_resolved_tree,
                                    scratch_pool);
      ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
    }

  conflict->resolution_tree = svn_client_conflict_option_get_id(option);

  return SVN_NO_ERROR;
}