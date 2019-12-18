#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
struct TYPE_33__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_34__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_ENTRY_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_NOT_LOCKED ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* svn_client__get_wc_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client__parse_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client__record_wc_mergeinfo (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 char* svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_mergeinfo__remove_empty_rangelists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_mergeinfo_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_mergeinfo_merge2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_nearest_ancestor ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_rangelist_merge2 (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_rangelist_remove (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_rangelist_reverse (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_wc_mergeinfo(svn_mergeinfo_catalog_t result_catalog,
                    const char *target_abspath,
                    const char *source_fspath,
                    apr_hash_t *merges,
                    svn_boolean_t is_rollback,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_index_t *hi;

  /* Combine the mergeinfo for the revision range just merged into
     the WC with its on-disk mergeinfo. */
  for (hi = apr_hash_first(scratch_pool, merges); hi; hi = apr_hash_next(hi))
    {
      const char *local_abspath = apr_hash_this_key(hi);
      svn_rangelist_t *ranges = apr_hash_this_val(hi);
      svn_rangelist_t *rangelist;
      svn_error_t *err;
      const char *local_abspath_rel_to_target;
      const char *fspath;
      svn_mergeinfo_t mergeinfo;

      svn_pool_clear(iterpool);

      /* As some of the merges may've changed the WC's mergeinfo, get
         a fresh copy before using it to update the WC's mergeinfo. */
      err = svn_client__parse_mergeinfo(&mergeinfo, ctx->wc_ctx,
                                        local_abspath, iterpool, iterpool);

      /* If a directory PATH was skipped because it is missing or was
         obstructed by an unversioned item then there's nothing we can
         do with that, so skip it. */
      if (err)
        {
          if (err->apr_err == SVN_ERR_WC_NOT_LOCKED
              || err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
            {
              svn_error_clear(err);
              continue;
            }
          else
            {
              return svn_error_trace(err);
            }
        }

      /* If we are attempting to set empty revision range override mergeinfo
         on a path with no explicit mergeinfo, we first need the
         mergeinfo that path inherits. */
      if (mergeinfo == NULL && ranges->nelts == 0)
        {
          SVN_ERR(svn_client__get_wc_mergeinfo(&mergeinfo, NULL,
                                               svn_mergeinfo_nearest_ancestor,
                                               local_abspath, NULL, NULL,
                                               FALSE, ctx, iterpool, iterpool));
        }

      if (mergeinfo == NULL)
        mergeinfo = apr_hash_make(iterpool);

      local_abspath_rel_to_target = svn_dirent_skip_ancestor(target_abspath,
                                                             local_abspath);
      SVN_ERR_ASSERT(local_abspath_rel_to_target != NULL);
      fspath = svn_fspath__join(source_fspath,
                                local_abspath_rel_to_target,
                                iterpool);
      rangelist = svn_hash_gets(mergeinfo, fspath);
      if (rangelist == NULL)
        rangelist = apr_array_make(iterpool, 0, sizeof(svn_merge_range_t *));

      if (is_rollback)
        {
          ranges = svn_rangelist_dup(ranges, iterpool);
          SVN_ERR(svn_rangelist_reverse(ranges, iterpool));
          SVN_ERR(svn_rangelist_remove(&rangelist, ranges, rangelist,
                                       FALSE,
                                       iterpool));
        }
      else
        {
          SVN_ERR(svn_rangelist_merge2(rangelist, ranges, iterpool, iterpool));
        }
      /* Update the mergeinfo by adjusting the path's rangelist. */
      svn_hash_sets(mergeinfo, fspath, rangelist);

      if (is_rollback && apr_hash_count(mergeinfo) == 0)
        mergeinfo = NULL;

      svn_mergeinfo__remove_empty_rangelists(mergeinfo, scratch_pool);

      if (result_catalog)
        {
          svn_mergeinfo_t existing_mergeinfo =
            svn_hash_gets(result_catalog, local_abspath);
          apr_pool_t *result_catalog_pool = apr_hash_pool_get(result_catalog);

          if (existing_mergeinfo)
            SVN_ERR(svn_mergeinfo_merge2(mergeinfo, existing_mergeinfo,
                                         result_catalog_pool, scratch_pool));
          svn_hash_sets(result_catalog,
                        apr_pstrdup(result_catalog_pool, local_abspath),
                        svn_mergeinfo_dup(mergeinfo, result_catalog_pool));
        }
      else
        {
          err = svn_client__record_wc_mergeinfo(local_abspath, mergeinfo,
                                                TRUE, ctx, iterpool);

          if (err && err->apr_err == SVN_ERR_ENTRY_NOT_FOUND)
            {
              /* PATH isn't just missing, it's not even versioned as far
                 as this working copy knows.  But it was included in
                 MERGES, which means that the server knows about it.
                 Likely we don't have access to the source due to authz
                 restrictions.  For now just clear the error and
                 continue...

                 ### TODO:  Set non-inheritable mergeinfo on PATH's immediate
                 ### parent and normal mergeinfo on PATH's siblings which we
                 ### do have access to. */
              svn_error_clear(err);
            }
          else
            SVN_ERR(err);
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}