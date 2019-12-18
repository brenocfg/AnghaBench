#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_19__ {struct notification_adjust_baton* notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_20__ {char* dst_abspath_or_url; scalar_t__ src_kind; int /*<<< orphan*/  src_revnum; int /*<<< orphan*/ * src_abspath_or_url; int /*<<< orphan*/  src_op_revision; int /*<<< orphan*/  src_peg_revision; int /*<<< orphan*/  src_original; } ;
typedef  TYPE_4__ svn_client__copy_pair_t ;
typedef  scalar_t__ svn_boolean_t ;
struct notification_adjust_baton {char const* checkout_abspath; char const* final_abspath; struct notification_adjust_baton* inner_baton; int /*<<< orphan*/  (* inner_func ) (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extend_wc_mergeinfo (char const*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notification_adjust_func (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_pinned_externals (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,TYPE_4__*,int /*<<< orphan*/ *,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct notification_adjust_baton*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__checkout_internal (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__copy_foreign (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__get_repos_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__handle_externals (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_dirent_join (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/ * svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_inherited ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_path_relative_to_session (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_buffered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__externals_gather_definitions (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__get_tmpdir (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_add_repos_file4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_copy3 (int /*<<< orphan*/ ,char const*,char const*,scalar_t__,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_add ; 
 int /*<<< orphan*/  svn_wc_notify_foreign_copy_begin ; 
 int /*<<< orphan*/ * svn_wc_prop_set4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_remove_from_revision_control2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
repos_to_wc_copy_single(svn_boolean_t *timestamp_sleep,
                        svn_client__copy_pair_t *pair,
                        svn_boolean_t same_repositories,
                        svn_boolean_t ignore_externals,
                        svn_boolean_t pin_externals,
                        const apr_hash_t *externals_to_pin,
                        svn_ra_session_t *ra_session,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *pool)
{
  apr_hash_t *src_mergeinfo;
  const char *dst_abspath = pair->dst_abspath_or_url;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_abspath));

  if (!same_repositories && ctx->notify_func2)
    {
      svn_wc_notify_t *notify;
      notify = svn_wc_create_notify_url(
                            pair->src_abspath_or_url,
                            svn_wc_notify_foreign_copy_begin,
                            pool);
      notify->kind = pair->src_kind;
      ctx->notify_func2(ctx->notify_baton2, notify, pool);

      /* Allow a theoretical cancel to get through. */
      if (ctx->cancel_func)
        SVN_ERR(ctx->cancel_func(ctx->cancel_baton));
    }

  if (pair->src_kind == svn_node_dir)
    {
      if (same_repositories)
        {
          const char *tmpdir_abspath, *tmp_abspath;

          /* Find a temporary location in which to check out the copy source. */
          SVN_ERR(svn_wc__get_tmpdir(&tmpdir_abspath, ctx->wc_ctx, dst_abspath,
                                     pool, pool));

          SVN_ERR(svn_io_open_unique_file3(NULL, &tmp_abspath, tmpdir_abspath,
                                           svn_io_file_del_on_close, pool, pool));

          /* Make a new checkout of the requested source. While doing so,
           * resolve pair->src_revnum to an actual revision number in case it
           * was until now 'invalid' meaning 'head'.  Ask this function not to
           * sleep for timestamps, by passing a sleep_needed output param.
           * Send notifications for all nodes except the root node, and adjust
           * them to refer to the destination rather than this temporary path. */
          {
            svn_wc_notify_func2_t old_notify_func2 = ctx->notify_func2;
            void *old_notify_baton2 = ctx->notify_baton2;
            struct notification_adjust_baton nb;
            svn_error_t *err;

            nb.inner_func = ctx->notify_func2;
            nb.inner_baton = ctx->notify_baton2;
            nb.checkout_abspath = tmp_abspath;
            nb.final_abspath = dst_abspath;
            ctx->notify_func2 = notification_adjust_func;
            ctx->notify_baton2 = &nb;

            /* Avoid a chicken-and-egg problem:
             * If pinning externals we'll need to adjust externals
             * properties before checking out any externals.
             * But copy needs to happen before pinning because else there
             * are no svn:externals properties to pin. */
            if (pin_externals)
              ignore_externals = TRUE;

            err = svn_client__checkout_internal(&pair->src_revnum, timestamp_sleep,
                                                pair->src_original,
                                                tmp_abspath,
                                                &pair->src_peg_revision,
                                                &pair->src_op_revision,
                                                svn_depth_infinity,
                                                ignore_externals, FALSE,
                                                ra_session, ctx, pool);

            ctx->notify_func2 = old_notify_func2;
            ctx->notify_baton2 = old_notify_baton2;

            SVN_ERR(err);
          }

          *timestamp_sleep = TRUE;

          /* Schedule dst_path for addition in parent, with copy history.
             Don't send any notification here.
             Then remove the temporary checkout's .svn dir in preparation for
             moving the rest of it into the final destination. */
          SVN_ERR(svn_wc_copy3(ctx->wc_ctx, tmp_abspath, dst_abspath,
                               TRUE /* metadata_only */,
                               ctx->cancel_func, ctx->cancel_baton,
                               NULL, NULL, pool));
          SVN_ERR(svn_wc__acquire_write_lock(NULL, ctx->wc_ctx, tmp_abspath,
                                             FALSE, pool, pool));
          SVN_ERR(svn_wc_remove_from_revision_control2(ctx->wc_ctx,
                                                       tmp_abspath,
                                                       FALSE, FALSE,
                                                       ctx->cancel_func,
                                                       ctx->cancel_baton,
                                                       pool));

          /* Move the temporary disk tree into place. */
          SVN_ERR(svn_io_file_rename2(tmp_abspath, dst_abspath, FALSE, pool));
        }
      else
        {
          *timestamp_sleep = TRUE;

          SVN_ERR(svn_client__copy_foreign(pair->src_abspath_or_url,
                                           dst_abspath,
                                           &pair->src_peg_revision,
                                           &pair->src_op_revision,
                                           svn_depth_infinity,
                                           FALSE /* make_parents */,
                                           TRUE /* already_locked */,
                                           ctx, pool));

          return SVN_NO_ERROR;
        }

      if (pin_externals)
        {
          apr_hash_t *pinned_externals;
          apr_hash_index_t *hi;
          apr_pool_t *iterpool;
          const char *repos_root_url;
          apr_hash_t *new_externals;
          apr_hash_t *new_depths;

          SVN_ERR(svn_ra_get_repos_root2(ra_session, &repos_root_url, pool));
          SVN_ERR(resolve_pinned_externals(&pinned_externals,
                                           externals_to_pin, pair,
                                           ra_session, repos_root_url,
                                           ctx, pool, pool));

          iterpool = svn_pool_create(pool);
          for (hi = apr_hash_first(pool, pinned_externals);
               hi;
               hi = apr_hash_next(hi))
            {
              const char *dst_relpath = apr_hash_this_key(hi);
              svn_string_t *externals_propval = apr_hash_this_val(hi);
              const char *local_abspath;

              svn_pool_clear(iterpool);

              local_abspath = svn_dirent_join(pair->dst_abspath_or_url,
                                              dst_relpath, iterpool);
              /* ### use a work queue? */
              SVN_ERR(svn_wc_prop_set4(ctx->wc_ctx, local_abspath,
                                       SVN_PROP_EXTERNALS, externals_propval,
                                       svn_depth_empty, TRUE /* skip_checks */,
                                       NULL  /* changelist_filter */,
                                       ctx->cancel_func, ctx->cancel_baton,
                                       NULL, NULL, /* no extra notification */
                                       iterpool));
            }

          /* Now update all externals in the newly created copy. */
          SVN_ERR(svn_wc__externals_gather_definitions(&new_externals,
                                                       &new_depths,
                                                       ctx->wc_ctx,
                                                       dst_abspath,
                                                       svn_depth_infinity,
                                                       iterpool, iterpool));
          SVN_ERR(svn_client__handle_externals(new_externals,
                                               new_depths,
                                               repos_root_url, dst_abspath,
                                               svn_depth_infinity,
                                               timestamp_sleep,
                                               ra_session,
                                               ctx, iterpool));
          svn_pool_destroy(iterpool);
        }
    } /* end directory case */

  else if (pair->src_kind == svn_node_file)
    {
      apr_hash_t *new_props;
      const char *src_rel;
      svn_stream_t *new_base_contents = svn_stream_buffered(pool);

      SVN_ERR(svn_ra_get_path_relative_to_session(ra_session, &src_rel,
                                                  pair->src_abspath_or_url,
                                                  pool));
      /* Fetch the file content. While doing so, resolve pair->src_revnum
       * to an actual revision number if it's 'invalid' meaning 'head'. */
      SVN_ERR(svn_ra_get_file(ra_session, src_rel, pair->src_revnum,
                              new_base_contents,
                              &pair->src_revnum, &new_props, pool));

      if (new_props && ! same_repositories)
        svn_hash_sets(new_props, SVN_PROP_MERGEINFO, NULL);

      *timestamp_sleep = TRUE;

      SVN_ERR(svn_wc_add_repos_file4(
         ctx->wc_ctx, dst_abspath,
         new_base_contents, NULL, new_props, NULL,
         same_repositories ? pair->src_abspath_or_url : NULL,
         same_repositories ? pair->src_revnum : SVN_INVALID_REVNUM,
         ctx->cancel_func, ctx->cancel_baton,
         pool));
    }

  /* Record the implied mergeinfo (before the notification callback
     is invoked for the root node). */
  SVN_ERR(svn_client__get_repos_mergeinfo(
            &src_mergeinfo, ra_session,
            pair->src_abspath_or_url, pair->src_revnum,
            svn_mergeinfo_inherited, TRUE /*squelch_incapable*/, pool));
  SVN_ERR(extend_wc_mergeinfo(dst_abspath, src_mergeinfo, ctx, pool));

  /* Do our own notification for the root node, even if we could possibly
     have delegated it.  See also issue #1552.

     ### Maybe this notification should mention the mergeinfo change. */
  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(
                                  dst_abspath, svn_wc_notify_add, pool);
      notify->kind = pair->src_kind;
      ctx->notify_func2(ctx->notify_baton2, notify, pool);
    }

  return SVN_NO_ERROR;
}