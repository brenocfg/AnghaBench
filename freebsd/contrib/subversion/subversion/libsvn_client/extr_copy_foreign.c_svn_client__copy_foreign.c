#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_8__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_EXISTS ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_foreign_dir (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client__make_local_parents (char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_2__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_writable (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_from_disk3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__copy_foreign(const char *url,
                         const char *dst_abspath,
                         svn_opt_revision_t *peg_revision,
                         svn_opt_revision_t *revision,
                         svn_depth_t depth,
                         svn_boolean_t make_parents,
                         svn_boolean_t already_locked,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  svn_client__pathrev_t *loc;
  svn_node_kind_t kind;
  svn_node_kind_t wc_kind;
  const char *dir_abspath;

  SVN_ERR_ASSERT(svn_path_is_url(url));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_abspath));

  /* Do we need to validate/update revisions? */

  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                            url, NULL,
                                            peg_revision,
                                            revision, ctx,
                                            scratch_pool));

  SVN_ERR(svn_ra_check_path(ra_session, "", loc->rev, &kind, scratch_pool));

  if (kind != svn_node_file && kind != svn_node_dir)
    return svn_error_createf(
                SVN_ERR_ILLEGAL_TARGET, NULL,
                _("'%s' is not a valid location inside a repository"),
                url);

  SVN_ERR(svn_wc_read_kind2(&wc_kind, ctx->wc_ctx, dst_abspath, FALSE, TRUE,
                            scratch_pool));

  if (wc_kind != svn_node_none)
    {
      return svn_error_createf(
                SVN_ERR_ENTRY_EXISTS, NULL,
                _("'%s' is already under version control"),
                svn_dirent_local_style(dst_abspath, scratch_pool));
    }

  dir_abspath = svn_dirent_dirname(dst_abspath, scratch_pool);
  SVN_ERR(svn_wc_read_kind2(&wc_kind, ctx->wc_ctx, dir_abspath,
                            FALSE, FALSE, scratch_pool));

  if (wc_kind == svn_node_none)
    {
      if (make_parents)
        SVN_ERR(svn_client__make_local_parents(dir_abspath, make_parents, ctx,
                                               scratch_pool));

      SVN_ERR(svn_wc_read_kind2(&wc_kind, ctx->wc_ctx, dir_abspath,
                                FALSE, FALSE, scratch_pool));
    }

  if (wc_kind != svn_node_dir)
    return svn_error_createf(
                SVN_ERR_ENTRY_NOT_FOUND, NULL,
                _("Can't add '%s', because no parent directory is found"),
                svn_dirent_local_style(dst_abspath, scratch_pool));


  if (kind == svn_node_file)
    {
      svn_stream_t *target;
      apr_hash_t *props;
      apr_hash_index_t *hi;
      SVN_ERR(svn_stream_open_writable(&target, dst_abspath, scratch_pool,
                                       scratch_pool));

      SVN_ERR(svn_ra_get_file(ra_session, "", loc->rev, target, NULL, &props,
                              scratch_pool));

      if (props != NULL)
        for (hi = apr_hash_first(scratch_pool, props); hi;
             hi = apr_hash_next(hi))
          {
            const char *name = apr_hash_this_key(hi);

            if (svn_property_kind2(name) != svn_prop_regular_kind
                || ! strcmp(name, SVN_PROP_MERGEINFO))
              {
                /* We can't handle DAV, ENTRY and merge specific props here */
                svn_hash_sets(props, name, NULL);
              }
          }

      if (!already_locked)
        SVN_WC__CALL_WITH_WRITE_LOCK(
              svn_wc_add_from_disk3(ctx->wc_ctx, dst_abspath, props,
                                    TRUE /* skip checks */,
                                    ctx->notify_func2, ctx->notify_baton2,
                                    scratch_pool),
              ctx->wc_ctx, dir_abspath, FALSE, scratch_pool);
      else
        SVN_ERR(svn_wc_add_from_disk3(ctx->wc_ctx, dst_abspath, props,
                                      TRUE /* skip checks */,
                                      ctx->notify_func2, ctx->notify_baton2,
                                      scratch_pool));
    }
  else
    {
      if (!already_locked)
        SVN_WC__CALL_WITH_WRITE_LOCK(
              copy_foreign_dir(ra_session, loc,
                               ctx->wc_ctx, dst_abspath,
                               depth,
                               ctx->notify_func2, ctx->notify_baton2,
                               ctx->cancel_func, ctx->cancel_baton,
                               scratch_pool),
              ctx->wc_ctx, dir_abspath, FALSE, scratch_pool);
      else
        SVN_ERR(copy_foreign_dir(ra_session, loc,
                                 ctx->wc_ctx, dst_abspath,
                                 depth,
                                 ctx->notify_func2, ctx->notify_baton2,
                                 ctx->cancel_func, ctx->cancel_baton,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}