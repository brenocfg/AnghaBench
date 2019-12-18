#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_12__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_13__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  char const apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  need_to_cache_iprops (scalar_t__*,char const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_ra_get_inherited_props (int /*<<< orphan*/ *,char const**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_cached_iprop_children (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_url (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_inheritable_props(apr_hash_t **wcroot_iprops,
                      const char *local_abspath,
                      svn_revnum_t revision,
                      svn_depth_t depth,
                      svn_ra_session_t *ra_session,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  apr_hash_t *iprop_paths;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_pool_t *session_pool = NULL;
  *wcroot_iprops = apr_hash_make(result_pool);

  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(revision));

  /* If we don't have a base revision for LOCAL_ABSPATH then it can't
     possibly be a working copy root, nor can it contain any WC roots
     in the form of switched subtrees.  So there is nothing to cache. */

  SVN_ERR(svn_wc__get_cached_iprop_children(&iprop_paths, depth,
                                            ctx->wc_ctx, local_abspath,
                                            scratch_pool, iterpool));

  /* If we are in the midst of a checkout or an update that is bringing in
     an external, then svn_wc__get_cached_iprop_children won't return
     LOCAL_ABSPATH in IPROPS_PATHS because the former has no cached iprops
     yet.  So make sure LOCAL_ABSPATH is present if it's a WC root. */
  if (!svn_hash_gets(iprop_paths, local_abspath))
    {
      svn_boolean_t needs_cached_iprops;

      SVN_ERR(need_to_cache_iprops(&needs_cached_iprops, local_abspath,
                                   ra_session, ctx, iterpool));
      if (needs_cached_iprops)
        {
          const char *target_abspath = apr_pstrdup(scratch_pool,
                                                   local_abspath);

          /* As value we set TARGET_ABSPATH, but any string besides ""
             would do */
          svn_hash_sets(iprop_paths, target_abspath, target_abspath);
        }
    }

      for (hi = apr_hash_first(scratch_pool, iprop_paths);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *child_abspath = apr_hash_this_key(hi);
          const char *child_repos_relpath = apr_hash_this_val(hi);
          const char *url;
          apr_array_header_t *inherited_props;
          svn_error_t *err;

          svn_pool_clear(iterpool);

          if (*child_repos_relpath == '\0')
            {
              /* A repository root doesn't have inherited properties */
              continue;
            }

          SVN_ERR(svn_wc__node_get_url(&url, ctx->wc_ctx, child_abspath,
                                       iterpool, iterpool));
          if (ra_session)
            SVN_ERR(svn_ra_reparent(ra_session, url, scratch_pool));
          else
            {
              if (! session_pool)
                session_pool = svn_pool_create(scratch_pool);

              SVN_ERR(svn_client_open_ra_session2(&ra_session, url, NULL,
                                                  ctx,
                                                  session_pool, iterpool));
            }

          err = svn_ra_get_inherited_props(ra_session, &inherited_props,
                                           "", revision,
                                           result_pool, iterpool);

          if (err)
            {
              if (err->apr_err != SVN_ERR_FS_NOT_FOUND)
                return svn_error_trace(err);

              svn_error_clear(err);
              continue;
            }

          svn_hash_sets(*wcroot_iprops,
                        apr_pstrdup(result_pool, child_abspath),
                        inherited_props);
        }


  svn_pool_destroy(iterpool);
  if (session_pool)
    svn_pool_destroy(session_pool);

  return SVN_NO_ERROR;

}