#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_25__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_26__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_27__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
typedef  void* svn_boolean_t ;
struct export_info_baton {char const* to_path; char const* native_eol; char const* origin_abspath; int /*<<< orphan*/  exported; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; void* ignore_keywords; void* overwrite; TYPE_2__ const* revision; } ;
struct edit_baton {char const* root_path; char const* native_eol; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; void* ignore_keywords; int /*<<< orphan*/  externals; int /*<<< orphan*/ * target_revision; void* force; int /*<<< orphan*/  root_url; int /*<<< orphan*/  repos_root_url; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_EV2_IMPL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * append_basename_if_dir (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 struct edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * export_directory (char const*,char const*,struct edit_baton*,TYPE_4__*,int /*<<< orphan*/ *,void*,void*,void*,int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * export_file (char const*,char const*,struct edit_baton*,TYPE_4__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * export_file_ev2 (char const*,char const*,struct edit_baton*,TYPE_4__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  export_node ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_cl__rev_default_to_head_or_working (TYPE_2__ const*,char const*) ; 
 TYPE_2__* svn_cl__rev_default_to_peg (TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/ * svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_4__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_url_from_path2 (char const**,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 void* svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_repos_root2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_completed ; 
 int /*<<< orphan*/ * svn_wc_walk_status (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct export_info_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_export5(svn_revnum_t *result_rev,
                   const char *from_path_or_url,
                   const char *to_path,
                   const svn_opt_revision_t *peg_revision,
                   const svn_opt_revision_t *revision,
                   svn_boolean_t overwrite,
                   svn_boolean_t ignore_externals,
                   svn_boolean_t ignore_keywords,
                   svn_depth_t depth,
                   const char *native_eol,
                   svn_client_ctx_t *ctx,
                   apr_pool_t *pool)
{
  svn_revnum_t edit_revision = SVN_INVALID_REVNUM;
  svn_boolean_t from_is_url = svn_path_is_url(from_path_or_url);

  SVN_ERR_ASSERT(peg_revision != NULL);
  SVN_ERR_ASSERT(revision != NULL);

  if (svn_path_is_url(to_path))
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a local path"), to_path);

  peg_revision = svn_cl__rev_default_to_head_or_working(peg_revision,
                                                        from_path_or_url);
  revision = svn_cl__rev_default_to_peg(revision, peg_revision);

  if (from_is_url || ! SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind))
    {
      svn_client__pathrev_t *loc;
      svn_ra_session_t *ra_session;
      svn_node_kind_t kind;
      const char *from_url;
      struct edit_baton *eb = apr_pcalloc(pool, sizeof(*eb));

      SVN_ERR(svn_client_url_from_path2(&from_url, from_path_or_url,
                                        ctx, pool, pool));

      /* Get the RA connection. */
      SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                                from_path_or_url, NULL,
                                                peg_revision,
                                                revision, ctx, pool));

      SVN_ERR(svn_ra_get_repos_root2(ra_session, &eb->repos_root_url, pool));
      eb->root_path = to_path;
      eb->root_url = loc->url;
      eb->force = overwrite;
      eb->target_revision = &edit_revision;
      eb->externals = apr_hash_make(pool);
      eb->native_eol = native_eol;
      eb->ignore_keywords = ignore_keywords;
      eb->cancel_func = ctx->cancel_func;
      eb->cancel_baton = ctx->cancel_baton;
      eb->notify_func = ctx->notify_func2;
      eb->notify_baton = ctx->notify_baton2;

      SVN_ERR(svn_ra_check_path(ra_session, "", loc->rev, &kind, pool));

      if (kind == svn_node_file)
        {
          if (!ENABLE_EV2_IMPL)
            SVN_ERR(export_file(from_url, to_path, eb, loc, ra_session,
                                overwrite, pool));
          else
            SVN_ERR(export_file_ev2(from_url, to_path, eb, loc,
                                    ra_session, overwrite, pool));
        }
      else if (kind == svn_node_dir)
        {
          SVN_ERR(export_directory(from_url, to_path,
                                   eb, loc, ra_session, overwrite,
                                   ignore_externals, ignore_keywords, depth,
                                   native_eol, ctx, pool));
        }
      else if (kind == svn_node_none)
        {
          return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                                   _("URL '%s' doesn't exist"),
                                   from_path_or_url);
        }
      /* kind == svn_node_unknown not handled */
    }
  else
    {
      struct export_info_baton eib;
      svn_node_kind_t kind;
      apr_hash_t *externals = NULL;

      /* This is a working copy export. */
      /* just copy the contents of the working copy into the target path. */
      SVN_ERR(svn_dirent_get_absolute(&from_path_or_url, from_path_or_url,
                                      pool));

      SVN_ERR(svn_dirent_get_absolute(&to_path, to_path, pool));

      SVN_ERR(svn_io_check_path(from_path_or_url, &kind, pool));

      /* ### [JAF] If something already exists on disk at the destination path,
       * the behaviour depends on the node kinds of the source and destination
       * and on the FORCE flag.  The intention (I guess) is to follow the
       * semantics of svn_client_export5(), semantics that are not fully
       * documented but would be something like:
       *
       * -----------+---------------------------------------------------------
       *        Src | DIR                 FILE                SPECIAL
       * Dst (disk) +---------------------------------------------------------
       * NONE       | simple copy         simple copy         (as src=file?)
       * DIR        | merge if forced [2] inside if root [1]  (as src=file?)
       * FILE       | err                 overwr if forced[3] (as src=file?)
       * SPECIAL    | ???                 ???                 ???
       * -----------+---------------------------------------------------------
       *
       * [1] FILE onto DIR case: If this file is the root of the copy and thus
       *     the only node to be copied, then copy it as a child of the
       *     directory TO, applying these same rules again except that if this
       *     case occurs again (the child path is already a directory) then
       *     error out.  If this file is not the root of the copy (it is
       *     reached by recursion), then error out.
       *
       * [2] DIR onto DIR case.  If the 'FORCE' flag is true then copy the
       *     source's children inside the target dir, else error out.  When
       *     copying the children, apply the same set of rules, except in the
       *     FILE onto DIR case error out like in note [1].
       *
       * [3] If the 'FORCE' flag is true then overwrite the destination file
       *     else error out.
       *
       * The reality (apparently, looking at the code) is somewhat different.
       * For a start, to detect the source kind, it looks at what is on disk
       * rather than the versioned working or base node.
       */
      if (kind == svn_node_file)
        SVN_ERR(append_basename_if_dir(&to_path, from_path_or_url, FALSE,
                                       pool));

      eib.to_path = to_path;
      eib.revision = revision;
      eib.overwrite = overwrite;
      eib.ignore_keywords = ignore_keywords;
      eib.wc_ctx = ctx->wc_ctx;
      eib.native_eol = native_eol;
      eib.notify_func = ctx->notify_func2;
      eib.notify_baton = ctx->notify_baton2;
      eib.origin_abspath = from_path_or_url;
      eib.exported = FALSE;

      SVN_ERR(svn_wc_walk_status(ctx->wc_ctx, from_path_or_url, depth,
                                 TRUE /* get_all */,
                                 TRUE /* no_ignore */,
                                 FALSE /* ignore_text_mods */,
                                 NULL,
                                 export_node, &eib,
                                 ctx->cancel_func, ctx->cancel_baton,
                                 pool));

      if (!eib.exported)
        return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                 _("The node '%s' was not found."),
                                 svn_dirent_local_style(from_path_or_url,
                                                        pool));

      if (!ignore_externals)
        SVN_ERR(svn_wc__externals_defined_below(&externals, ctx->wc_ctx,
                                                from_path_or_url,
                                                pool, pool));

      if (externals && apr_hash_count(externals))
        {
          apr_pool_t *iterpool = svn_pool_create(pool);
          apr_hash_index_t *hi;

          for (hi = apr_hash_first(pool, externals);
               hi;
               hi = apr_hash_next(hi))
            {
              const char *external_abspath = apr_hash_this_key(hi);
              const char *relpath;
              const char *target_abspath;

              svn_pool_clear(iterpool);

              relpath = svn_dirent_skip_ancestor(from_path_or_url,
                                                 external_abspath);

              target_abspath = svn_dirent_join(to_path, relpath,
                                                         iterpool);

              /* Ensure that the parent directory exists */
              SVN_ERR(svn_io_make_dir_recursively(
                            svn_dirent_dirname(target_abspath, iterpool),
                            iterpool));

              SVN_ERR(svn_client_export5(NULL,
                                         svn_dirent_join(from_path_or_url,
                                                         relpath,
                                                         iterpool),
                                         target_abspath,
                                         peg_revision, revision,
                                         TRUE, ignore_externals,
                                         ignore_keywords, depth, native_eol,
                                         ctx, iterpool));
            }

          svn_pool_destroy(iterpool);
        }
    }


  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify
        = svn_wc_create_notify(to_path,
                               svn_wc_notify_update_completed, pool);
      notify->revision = edit_revision;
      ctx->notify_func2(ctx->notify_baton2, notify, pool);
    }

  if (result_rev)
    *result_rev = edit_revision;

  return SVN_NO_ERROR;
}