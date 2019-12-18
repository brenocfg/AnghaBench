#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__node_get_changed_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
obtain_eol_and_keywords_for_file(apr_hash_t **keywords,
                                 svn_subst_eol_style_t *eol_style,
                                 const char **eol_str,
                                 svn_wc_context_t *wc_ctx,
                                 const char *local_abspath,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  svn_string_t *keywords_val, *eol_style_val;

  SVN_ERR(svn_wc_prop_list2(&props, wc_ctx, local_abspath,
                            scratch_pool, scratch_pool));
  keywords_val = svn_hash_gets(props, SVN_PROP_KEYWORDS);
  if (keywords_val)
    {
      svn_revnum_t changed_rev;
      apr_time_t changed_date;
      const char *rev_str;
      const char *author;
      const char *url;
      const char *repos_root_url;
      const char *repos_relpath;

      SVN_ERR(svn_wc__node_get_changed_info(&changed_rev,
                                            &changed_date,
                                            &author, wc_ctx,
                                            local_abspath,
                                            scratch_pool,
                                            scratch_pool));
      rev_str = apr_psprintf(scratch_pool, "%ld", changed_rev);
      SVN_ERR(svn_wc__node_get_repos_info(NULL, &repos_relpath, &repos_root_url,
                                          NULL,
                                          wc_ctx, local_abspath,
                                          scratch_pool, scratch_pool));
      url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                        scratch_pool);

      SVN_ERR(svn_subst_build_keywords3(keywords,
                                        keywords_val->data,
                                        rev_str, url, repos_root_url,
                                        changed_date,
                                        author, result_pool));
    }

  eol_style_val = svn_hash_gets(props, SVN_PROP_EOL_STYLE);
  if (eol_style_val)
    {
      svn_subst_eol_style_from_value(eol_style,
                                     eol_str,
                                     eol_style_val->data);
    }

  return SVN_NO_ERROR;
}