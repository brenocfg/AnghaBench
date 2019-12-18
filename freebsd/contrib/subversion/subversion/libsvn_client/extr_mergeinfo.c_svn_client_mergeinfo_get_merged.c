#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  scalar_t__ svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_mergeinfo (scalar_t__*,char const**,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mergeinfo_relpaths_to_urls (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_mergeinfo_get_merged(apr_hash_t **mergeinfo_p,
                                const char *path_or_url,
                                const svn_opt_revision_t *peg_revision,
                                svn_client_ctx_t *ctx,
                                apr_pool_t *pool)
{
  const char *repos_root;
  svn_mergeinfo_catalog_t mergeinfo_cat;
  svn_mergeinfo_t mergeinfo;

  SVN_ERR(get_mergeinfo(&mergeinfo_cat, &repos_root, path_or_url,
                        peg_revision, FALSE, FALSE, ctx, NULL, pool, pool));
  if (mergeinfo_cat)
    {
      const char *repos_relpath;

      if (! svn_path_is_url(path_or_url))
        {
          SVN_ERR(svn_dirent_get_absolute(&path_or_url, path_or_url, pool));
          SVN_ERR(svn_wc__node_get_repos_info(NULL, &repos_relpath, NULL, NULL,
                                              ctx->wc_ctx, path_or_url,
                                              pool, pool));
        }
      else
        {
          repos_relpath = svn_uri_skip_ancestor(repos_root, path_or_url, pool);

          SVN_ERR_ASSERT(repos_relpath != NULL); /* Or get_mergeinfo failed */
        }

      mergeinfo = svn_hash_gets(mergeinfo_cat, repos_relpath);
    }
  else
    {
      mergeinfo = NULL;
    }

  SVN_ERR(mergeinfo_relpaths_to_urls(mergeinfo_p, mergeinfo,
                                     repos_root, pool, pool));
  return SVN_NO_ERROR;
}