#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_client__get_repos_mergeinfo_catalog (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_wc_mergeinfo_catalog (int /*<<< orphan*/ **,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_mergeinfo_catalog_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_explicit ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_wc_or_repos_mergeinfo_catalog(
  svn_mergeinfo_catalog_t *target_mergeinfo_catalog,
  svn_boolean_t *inherited_p,
  svn_boolean_t *from_repos,
  svn_boolean_t include_descendants,
  svn_boolean_t repos_only,
  svn_boolean_t ignore_invalid_mergeinfo,
  svn_mergeinfo_inheritance_t inherit,
  svn_ra_session_t *ra_session,
  const char *target_wcpath,
  svn_client_ctx_t *ctx,
  apr_pool_t *result_pool,
  apr_pool_t *scratch_pool)
{
  const char *url;
  svn_revnum_t target_rev;
  const char *local_abspath;
  const char *repos_root;
  const char *repos_relpath;
  svn_mergeinfo_catalog_t target_mergeinfo_cat_wc = NULL;
  svn_mergeinfo_catalog_t target_mergeinfo_cat_repos = NULL;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, target_wcpath,
                                  scratch_pool));

  if (from_repos)
    *from_repos = FALSE;

  /* We may get an entry with abbreviated information from TARGET_WCPATH's
     parent if TARGET_WCPATH is missing.  These limited entries do not have
     a URL and without that we cannot get accurate mergeinfo for
     TARGET_WCPATH. */
  SVN_ERR(svn_wc__node_get_origin(NULL, &target_rev, &repos_relpath,
                                  &repos_root, NULL, NULL, NULL,
                                  ctx->wc_ctx, local_abspath, FALSE,
                                  scratch_pool, scratch_pool));

  if (repos_relpath)
    url = svn_path_url_add_component2(repos_root, repos_relpath, scratch_pool);
  else
    url = NULL;

  if (!repos_only)
    {
      svn_boolean_t inherited;
      SVN_ERR(svn_client__get_wc_mergeinfo_catalog(&target_mergeinfo_cat_wc,
                                                   &inherited,
                                                   include_descendants,
                                                   inherit,
                                                   local_abspath,
                                                   NULL, NULL,
                                                   ignore_invalid_mergeinfo,
                                                   ctx,
                                                   result_pool,
                                                   scratch_pool));
      if (inherited_p)
        *inherited_p = inherited;

      /* If we want LOCAL_ABSPATH's inherited mergeinfo, were we able to
         get it from the working copy?  If not, then we must ask the
         repository. */
      if (! (inherited
             || (inherit == svn_mergeinfo_explicit)
             || (repos_relpath
                 && target_mergeinfo_cat_wc
                 && svn_hash_gets(target_mergeinfo_cat_wc, repos_relpath))))
        {
          repos_only = TRUE;
          /* We already have any subtree mergeinfo from the working copy, no
             need to ask the server for it again. */
          include_descendants = FALSE;
        }
    }

  if (repos_only)
    {
      /* No need to check the repos if this is a local addition. */
      if (url != NULL)
        {
          apr_hash_t *original_props;

          /* Check to see if we have local modifications which removed all of
             TARGET_WCPATH's pristine mergeinfo.  If that is the case then
             TARGET_WCPATH effectively has no mergeinfo. */
          SVN_ERR(svn_wc_get_pristine_props(&original_props,
                                            ctx->wc_ctx, local_abspath,
                                            result_pool, scratch_pool));
          if (!svn_hash_gets(original_props, SVN_PROP_MERGEINFO))
            {
              apr_pool_t *sesspool = NULL;

              if (! ra_session)
                {
                  sesspool = svn_pool_create(scratch_pool);
                  SVN_ERR(svn_client_open_ra_session2(&ra_session, url, NULL,
                                                      ctx,
                                                      sesspool, sesspool));
                }

              SVN_ERR(svn_client__get_repos_mergeinfo_catalog(
                        &target_mergeinfo_cat_repos, ra_session,
                        url, target_rev, inherit,
                        TRUE, include_descendants,
                        result_pool, scratch_pool));

              if (target_mergeinfo_cat_repos
                  && svn_hash_gets(target_mergeinfo_cat_repos, repos_relpath))
                {
                  if (inherited_p)
                    *inherited_p = TRUE;
                  if (from_repos)
                    *from_repos = TRUE;
                }

              /* If we created an RA_SESSION above, destroy it.
                 Otherwise, if reparented an existing session, point
                 it back where it was when we were called. */
              if (sesspool)
                {
                  svn_pool_destroy(sesspool);
                }
            }
        }
    }

  /* Combine the mergeinfo from the working copy and repository as needed. */
  if (target_mergeinfo_cat_wc)
    {
      *target_mergeinfo_catalog = target_mergeinfo_cat_wc;
      if (target_mergeinfo_cat_repos)
        SVN_ERR(svn_mergeinfo_catalog_merge(*target_mergeinfo_catalog,
                                            target_mergeinfo_cat_repos,
                                            result_pool, scratch_pool));
    }
  else if (target_mergeinfo_cat_repos)
    {
      *target_mergeinfo_catalog = target_mergeinfo_cat_repos;
    }
  else
    {
      *target_mergeinfo_catalog = NULL;
    }

  return SVN_NO_ERROR;
}