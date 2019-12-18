#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_client__get_wc_mergeinfo (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,char const*,char const*,char const**,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__prop_retrieve_recursive (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_wc_mergeinfo_catalog(svn_mergeinfo_catalog_t *mergeinfo_cat,
                                     svn_boolean_t *inherited,
                                     svn_boolean_t include_descendants,
                                     svn_mergeinfo_inheritance_t inherit,
                                     const char *local_abspath,
                                     const char *limit_path,
                                     const char **walked_path,
                                     svn_boolean_t ignore_invalid_mergeinfo,
                                     svn_client_ctx_t *ctx,
                                     apr_pool_t *result_pool,
                                     apr_pool_t *scratch_pool)
{
  const char *target_repos_relpath;
  svn_mergeinfo_t mergeinfo;
  const char *repos_root;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  *mergeinfo_cat = NULL;
  SVN_ERR(svn_wc__node_get_repos_info(NULL, &target_repos_relpath,
                                      &repos_root, NULL,
                                      ctx->wc_ctx, local_abspath,
                                      scratch_pool, scratch_pool));

  /* Get the mergeinfo for the LOCAL_ABSPATH target and set *INHERITED and
     *WALKED_PATH. */
  SVN_ERR(svn_client__get_wc_mergeinfo(&mergeinfo, inherited, inherit,
                                       local_abspath, limit_path,
                                       walked_path, ignore_invalid_mergeinfo,
                                       ctx, result_pool, scratch_pool));

  /* Add any explicit/inherited mergeinfo for LOCAL_ABSPATH to
     *MERGEINFO_CAT. */
  if (mergeinfo)
    {
      *mergeinfo_cat = apr_hash_make(result_pool);
      svn_hash_sets(*mergeinfo_cat,
                    apr_pstrdup(result_pool, target_repos_relpath), mergeinfo);
    }

  /* If LOCAL_ABSPATH is a directory and we want the subtree mergeinfo too,
     then get it.

     With WC-NG it is cheaper to do a single db transaction, than first
     looking if we really have a directory. */
  if (include_descendants)
    {
      apr_hash_t *mergeinfo_props;
      apr_hash_index_t *hi;

      SVN_ERR(svn_wc__prop_retrieve_recursive(&mergeinfo_props,
                                              ctx->wc_ctx, local_abspath,
                                              SVN_PROP_MERGEINFO,
                                              scratch_pool, scratch_pool));

      /* Convert *mergeinfo_props into a proper svn_mergeinfo_catalog_t */
      for (hi = apr_hash_first(scratch_pool, mergeinfo_props);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *node_abspath = apr_hash_this_key(hi);
          svn_string_t *propval = apr_hash_this_val(hi);
          svn_mergeinfo_t subtree_mergeinfo;
          const char *repos_relpath;

          if (strcmp(node_abspath, local_abspath) == 0)
            continue; /* Already parsed in svn_client__get_wc_mergeinfo */

          SVN_ERR(svn_wc__node_get_repos_info(NULL, &repos_relpath, NULL, NULL,
                                              ctx->wc_ctx, node_abspath,
                                              result_pool, scratch_pool));

          SVN_ERR(svn_mergeinfo_parse(&subtree_mergeinfo, propval->data,
                                      result_pool));

          /* If the target had no explicit/inherited mergeinfo and this is the
             first subtree with mergeinfo found, then the catalog will still
             be NULL. */
          if (*mergeinfo_cat == NULL)
            *mergeinfo_cat = apr_hash_make(result_pool);

          svn_hash_sets(*mergeinfo_cat, repos_relpath, subtree_mergeinfo);
        }
    }

  return SVN_NO_ERROR;
}