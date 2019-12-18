#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_39__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_40__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
struct TYPE_41__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_42__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_4__ svn_client_ctx_t ;
struct TYPE_43__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_5__ svn_client__pathrev_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_IS_DIRECTORY ; 
 scalar_t__ SVN_ERR_FS_NOT_FILE ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_cl__rev_default_to_head_or_base (TYPE_2__ const*,char const*) ; 
 TYPE_2__* svn_cl__rev_default_to_head_or_working (TYPE_2__ const*,char const*) ; 
 TYPE_2__* svn_cl__rev_default_to_peg (TYPE_2__ const*,TYPE_2__ const*) ; 
 TYPE_3__* svn_client__get_normalized_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_5__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 TYPE_3__* svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stream_close (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_none ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_is_normal_prop (void const*) ; 
 TYPE_3__* svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_cat3(apr_hash_t **returned_props,
                svn_stream_t *out,
                const char *path_or_url,
                const svn_opt_revision_t *peg_revision,
                const svn_opt_revision_t *revision,
                svn_boolean_t expand_keywords,
                svn_client_ctx_t *ctx,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  svn_client__pathrev_t *loc;
  svn_string_t *eol_style;
  svn_string_t *keywords;
  apr_hash_t *props = NULL;
  const char *repos_root_url;
  svn_stream_t *output = out;
  svn_error_t *err;

  /* ### Inconsistent default revision logic in this command. */
  if (peg_revision->kind == svn_opt_revision_unspecified)
    {
      peg_revision = svn_cl__rev_default_to_head_or_working(peg_revision,
                                                            path_or_url);
      revision = svn_cl__rev_default_to_head_or_base(revision, path_or_url);
    }
  else
    {
      revision = svn_cl__rev_default_to_peg(revision, peg_revision);
    }

  if (! svn_path_is_url(path_or_url)
      && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(peg_revision->kind)
      && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind))
    {
      const char *local_abspath;
      svn_stream_t *normal_stream;

      SVN_ERR(svn_dirent_get_absolute(&local_abspath, path_or_url,
                                      scratch_pool));
      SVN_ERR(svn_client__get_normalized_stream(&normal_stream, ctx->wc_ctx,
                                            local_abspath, revision,
                                            expand_keywords, FALSE,
                                            ctx->cancel_func, ctx->cancel_baton,
                                            scratch_pool, scratch_pool));

      /* We don't promise to close output, so disown it to ensure we don't. */
      output = svn_stream_disown(output, scratch_pool);

      if (returned_props)
        SVN_ERR(svn_wc_prop_list2(returned_props, ctx->wc_ctx, local_abspath,
                                  result_pool, scratch_pool));

      return svn_error_trace(svn_stream_copy3(normal_stream, output,
                                              ctx->cancel_func,
                                              ctx->cancel_baton, scratch_pool));
    }

  /* Get an RA plugin for this filesystem object. */
  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                            path_or_url, NULL,
                                            peg_revision,
                                            revision, ctx, scratch_pool));

  /* Find the repos root URL */
  SVN_ERR(svn_ra_get_repos_root2(ra_session, &repos_root_url, scratch_pool));

  /* Grab some properties we need to know in order to figure out if anything
     special needs to be done with this file. */
  err = svn_ra_get_file(ra_session, "", loc->rev, NULL, NULL, &props,
                        result_pool);
  if (err)
    {
      if (err->apr_err == SVN_ERR_FS_NOT_FILE)
        {
          return svn_error_createf(SVN_ERR_CLIENT_IS_DIRECTORY, err,
                                   _("URL '%s' refers to a directory"),
                                   loc->url);
        }
      else
        {
          return svn_error_trace(err);
        }
    }

  eol_style = svn_hash_gets(props, SVN_PROP_EOL_STYLE);
  keywords = svn_hash_gets(props, SVN_PROP_KEYWORDS);

  if (eol_style || keywords)
    {
      /* It's a file with no special eol style or keywords. */
      svn_subst_eol_style_t eol;
      const char *eol_str;
      apr_hash_t *kw;

      if (eol_style)
        svn_subst_eol_style_from_value(&eol, &eol_str, eol_style->data);
      else
        {
          eol = svn_subst_eol_style_none;
          eol_str = NULL;
        }


      if (keywords && expand_keywords)
        {
          svn_string_t *cmt_rev, *cmt_date, *cmt_author;
          apr_time_t when = 0;

          cmt_rev = svn_hash_gets(props, SVN_PROP_ENTRY_COMMITTED_REV);
          cmt_date = svn_hash_gets(props, SVN_PROP_ENTRY_COMMITTED_DATE);
          cmt_author = svn_hash_gets(props, SVN_PROP_ENTRY_LAST_AUTHOR);
          if (cmt_date)
            SVN_ERR(svn_time_from_cstring(&when, cmt_date->data, scratch_pool));

          SVN_ERR(svn_subst_build_keywords3(&kw, keywords->data,
                                            cmt_rev->data, loc->url,
                                            repos_root_url, when,
                                            cmt_author ?
                                              cmt_author->data : NULL,
                                            scratch_pool));
        }
      else
        kw = NULL;

      /* Interject a translating stream */
      output = svn_subst_stream_translated(svn_stream_disown(out,
                                                             scratch_pool),
                                           eol_str, FALSE, kw, TRUE,
                                           scratch_pool);
    }

  if (returned_props)
    {
      /* filter entry and WC props */
      apr_hash_index_t *hi;
      const void *key;
      apr_ssize_t klen;

      for (hi = apr_hash_first(scratch_pool, props);
           hi; hi = apr_hash_next(hi))
        {
          apr_hash_this(hi, &key, &klen, NULL);
          if (!svn_wc_is_normal_prop(key))
            apr_hash_set(props, key, klen, NULL);
        }

      *returned_props = props;
    }

  SVN_ERR(svn_ra_get_file(ra_session, "", loc->rev, output, NULL, NULL,
                          scratch_pool));

  if (out != output)
    /* Close the interjected stream */
    SVN_ERR(svn_stream_close(output));

  return SVN_NO_ERROR;
}