#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ node_status; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_9__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_IS_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_UNVERSIONED_RESOURCE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 char const* SVN_SUBST_NATIVE_EOL_STR ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_affected_time (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_opt_revision_working ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_changed_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_contents2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ *,char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_status3 (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_status_normal ; 

svn_error_t *
svn_client__get_normalized_stream(svn_stream_t **normal_stream,
                                  svn_wc_context_t *wc_ctx,
                                  const char *local_abspath,
                                  const svn_opt_revision_t *revision,
                                  svn_boolean_t expand_keywords,
                                  svn_boolean_t normalize_eols,
                                  svn_cancel_func_t cancel_func,
                                  void *cancel_baton,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  apr_hash_t *kw = NULL;
  svn_subst_eol_style_t style;
  apr_hash_t *props;
  svn_string_t *eol_style, *keywords, *special;
  const char *eol = NULL;
  svn_boolean_t local_mod = FALSE;
  svn_stream_t *input;
  svn_node_kind_t kind;

  SVN_ERR_ASSERT(SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind));

  SVN_ERR(svn_wc_read_kind2(&kind, wc_ctx, local_abspath,
                            (revision->kind != svn_opt_revision_working),
                            FALSE, scratch_pool));

  if (kind == svn_node_unknown || kind == svn_node_none)
    return svn_error_createf(SVN_ERR_UNVERSIONED_RESOURCE, NULL,
                             _("'%s' is not under version control"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (kind != svn_node_file)
    return svn_error_createf(SVN_ERR_CLIENT_IS_DIRECTORY, NULL,
                             _("'%s' refers to a directory"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  if (revision->kind != svn_opt_revision_working)
    {
      SVN_ERR(svn_wc_get_pristine_contents2(&input, wc_ctx, local_abspath,
                                            result_pool, scratch_pool));
      if (input == NULL)
        return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                 _("'%s' has no pristine version until it is committed"),
                 svn_dirent_local_style(local_abspath, scratch_pool));

      SVN_ERR(svn_wc_get_pristine_props(&props, wc_ctx, local_abspath,
                                        scratch_pool, scratch_pool));
    }
  else
    {
      svn_wc_status3_t *status;

      SVN_ERR(svn_stream_open_readonly(&input, local_abspath, scratch_pool,
                                       result_pool));

      SVN_ERR(svn_wc_prop_list2(&props, wc_ctx, local_abspath, scratch_pool,
                                scratch_pool));
      SVN_ERR(svn_wc_status3(&status, wc_ctx, local_abspath, scratch_pool,
                             scratch_pool));
      if (status->node_status != svn_wc_status_normal)
        local_mod = TRUE;
    }

  eol_style = svn_hash_gets(props, SVN_PROP_EOL_STYLE);
  keywords = svn_hash_gets(props, SVN_PROP_KEYWORDS);
  special = svn_hash_gets(props, SVN_PROP_SPECIAL);

  if (eol_style)
    svn_subst_eol_style_from_value(&style, &eol, eol_style->data);

  if (keywords)
    {
      svn_revnum_t changed_rev;
      const char *rev_str;
      const char *author;
      const char *url;
      apr_time_t tm;
      const char *repos_root_url;
      const char *repos_relpath;

      SVN_ERR(svn_wc__node_get_changed_info(&changed_rev, &tm, &author, wc_ctx,
                                            local_abspath, scratch_pool,
                                            scratch_pool));
      SVN_ERR(svn_wc__node_get_repos_info(NULL, &repos_relpath, &repos_root_url,
                                          NULL,
                                          wc_ctx, local_abspath, scratch_pool,
                                          scratch_pool));
      url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                        scratch_pool);

      if (local_mod)
        {
          /* For locally modified files, we'll append an 'M'
             to the revision number, and set the author to
             "(local)" since we can't always determine the
             current user's username */
          rev_str = apr_psprintf(scratch_pool, "%ldM", changed_rev);
          author = _("(local)");

          if (! special)
            {
              /* Use the modified time from the working copy for files */
              SVN_ERR(svn_io_file_affected_time(&tm, local_abspath,
                                                scratch_pool));
            }
        }
      else
        {
          rev_str = apr_psprintf(scratch_pool, "%ld", changed_rev);
        }

      SVN_ERR(svn_subst_build_keywords3(&kw, keywords->data, rev_str, url,
                                        repos_root_url, tm, author,
                                        scratch_pool));
    }

  /* Wrap the output stream if translation is needed. */
  if (eol != NULL || kw != NULL)
    input = svn_subst_stream_translated(
      input,
      (eol_style && normalize_eols) ? SVN_SUBST_NATIVE_EOL_STR : eol,
      FALSE, kw, expand_keywords, result_pool);

  *normal_stream = input;

  return SVN_NO_ERROR;
}