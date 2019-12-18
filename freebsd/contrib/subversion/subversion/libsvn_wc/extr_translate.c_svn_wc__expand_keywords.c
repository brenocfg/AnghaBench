#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_repos_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__expand_keywords(apr_hash_t **keywords,
                        svn_wc__db_t *db,
                        const char *local_abspath,
                        const char *wri_abspath,
                        const char *keyword_list,
                        svn_boolean_t for_normalization,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_revnum_t changed_rev;
  apr_time_t changed_date;
  const char *changed_author;
  const char *url;
  const char *repos_root_url;

  if (! for_normalization)
    {
      const char *repos_relpath;

      SVN_ERR(svn_wc__db_read_info(NULL, NULL, NULL, &repos_relpath,
                                   &repos_root_url, NULL, &changed_rev,
                                   &changed_date, &changed_author, NULL,
                                   NULL, NULL, NULL, NULL, NULL, NULL,
                                   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                   NULL, NULL, NULL, NULL,
                                   db, local_abspath,
                                   scratch_pool, scratch_pool));

      /* Handle special statuses (e.g. added) */
      if (!repos_relpath)
         SVN_ERR(svn_wc__db_read_repos_info(NULL, &repos_relpath,
                                            &repos_root_url, NULL,
                                            db, local_abspath,
                                            scratch_pool, scratch_pool));

      url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                        scratch_pool);
    }
  else
    {
      url = "";
      changed_rev = SVN_INVALID_REVNUM;
      changed_date = 0;
      changed_author = "";
      repos_root_url = "";
    }

  SVN_ERR(svn_subst_build_keywords3(keywords, keyword_list,
                                    apr_psprintf(scratch_pool, "%ld",
                                                 changed_rev),
                                    url, repos_root_url,
                                    changed_date, changed_author,
                                    result_pool));

  if (apr_hash_count(*keywords) == 0)
    *keywords = NULL;

  return SVN_NO_ERROR;
}