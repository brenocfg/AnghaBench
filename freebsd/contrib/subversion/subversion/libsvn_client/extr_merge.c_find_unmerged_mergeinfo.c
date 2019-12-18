#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
struct TYPE_18__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_19__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ svn_client__pathrev_t ;
struct TYPE_20__ {TYPE_2__ const loc; } ;
typedef  TYPE_3__ merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_ERR_RA_DAV_REQUEST_FAILED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_unmerged_mergeinfo_subroutine (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_youngest_merged_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_url_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client__get_history_as_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_repos_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__pathrev_create_with_session (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client__pathrev_join_relpath (TYPE_2__ const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_client__pathrev_relpath (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo__filter_catalog_by_ranges (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo__filter_mergeinfo_by_ranges (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_mergeinfo_catalog_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_inherited ; 
 scalar_t__ svn_node_none ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
find_unmerged_mergeinfo(svn_mergeinfo_catalog_t *unmerged_to_source_catalog,
                        svn_revnum_t *youngest_merged_rev,
                        svn_revnum_t yc_ancestor_rev,
                        svn_mergeinfo_catalog_t source_catalog,
                        apr_hash_t *target_history_hash,
                        const svn_client__pathrev_t *source_loc,
                        const merge_target_t *target,
                        svn_ra_session_t *source_ra_session,
                        svn_ra_session_t *target_ra_session,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const char *source_repos_rel_path
    = svn_client__pathrev_relpath(source_loc, scratch_pool);
  const char *target_repos_rel_path
    = svn_client__pathrev_relpath(&target->loc, scratch_pool);
  apr_hash_index_t *hi;
  svn_mergeinfo_catalog_t new_catalog = apr_hash_make(result_pool);
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  assert(session_url_is(source_ra_session, source_loc->url, scratch_pool));
  assert(session_url_is(target_ra_session, target->loc.url, scratch_pool));

  *youngest_merged_rev = SVN_INVALID_REVNUM;

  /* Examine the natural history of each path in the reintegrate target
     with explicit mergeinfo. */
  for (hi = apr_hash_first(scratch_pool, target_history_hash);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *target_path = apr_hash_this_key(hi);
      svn_mergeinfo_t target_history_as_mergeinfo = apr_hash_this_val(hi);
      const char *path_rel_to_session
        = svn_relpath_skip_ancestor(target_repos_rel_path, target_path);
      const char *source_path;
      svn_client__pathrev_t *source_pathrev;
      svn_mergeinfo_t source_mergeinfo, filtered_mergeinfo;

      svn_pool_clear(iterpool);

      source_path = svn_relpath_join(source_repos_rel_path,
                                     path_rel_to_session, iterpool);
      source_pathrev = svn_client__pathrev_join_relpath(
                         source_loc, path_rel_to_session, iterpool);

      /* Remove any target history that is also part of the source's history,
         i.e. their common ancestry.  By definition this has already been
         "merged" from the target to the source.  If the source has explicit
         self referential mergeinfo it would intersect with the target's
         history below, making it appear that some merges had been done from
         the target to the source, when this might not actually be the case. */
      SVN_ERR(svn_mergeinfo__filter_mergeinfo_by_ranges(
        &target_history_as_mergeinfo, target_history_as_mergeinfo,
        source_loc->rev, yc_ancestor_rev, TRUE, iterpool, iterpool));

      /* Look for any explicit mergeinfo on the source path corresponding to
         the target path.  If we find any remove that from SOURCE_CATALOG.
         When this iteration over TARGET_HISTORY_HASH is complete all that
         should be left in SOURCE_CATALOG are subtrees that have explicit
         mergeinfo on the reintegrate source where there is no corresponding
         explicit mergeinfo on the reintegrate target. */
      source_mergeinfo = svn_hash_gets(source_catalog, source_path);
      if (source_mergeinfo)
        {
          svn_hash_sets(source_catalog, source_path, NULL);

          SVN_ERR(find_youngest_merged_rev(youngest_merged_rev,
                                           target_history_as_mergeinfo,
                                           source_mergeinfo,
                                           iterpool));
        }
      else
        {
          /* There is no mergeinfo on source_path *or* source_path doesn't
             exist at all.  If simply doesn't exist we can ignore it
             altogether. */
          svn_node_kind_t kind;

          SVN_ERR(svn_ra_check_path(source_ra_session,
                                    path_rel_to_session,
                                    source_loc->rev, &kind, iterpool));
          if (kind == svn_node_none)
              continue;
          /* Else source_path does exist though it has no explicit mergeinfo.
             Find its inherited mergeinfo.  If it doesn't have any then simply
             set source_mergeinfo to an empty hash. */
          SVN_ERR(svn_client__get_repos_mergeinfo(
                    &source_mergeinfo, source_ra_session,
                    source_pathrev->url, source_pathrev->rev,
                    svn_mergeinfo_inherited, FALSE /*squelch_incapable*/,
                    iterpool));
          if (!source_mergeinfo)
            source_mergeinfo = apr_hash_make(iterpool);
        }

      /* Use scratch_pool rather than iterpool because filtered_mergeinfo
         is going into new_catalog below and needs to last to the end of
         this function. */
      SVN_ERR(find_unmerged_mergeinfo_subroutine(
                &filtered_mergeinfo, target_history_as_mergeinfo,
                source_mergeinfo, source_pathrev,
                source_ra_session, ctx, scratch_pool, iterpool));
      svn_hash_sets(new_catalog, apr_pstrdup(scratch_pool, source_path),
                    filtered_mergeinfo);
    }

  /* Are there any subtrees with explicit mergeinfo still left in the merge
     source where there was no explicit mergeinfo for the corresponding path
     in the merge target?  If so, add the intersection of those path's
     mergeinfo and the corresponding target path's mergeinfo to
     new_catalog. */
  for (hi = apr_hash_first(scratch_pool, source_catalog);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *source_path = apr_hash_this_key(hi);
      const char *path_rel_to_session =
        svn_relpath_skip_ancestor(source_repos_rel_path, source_path);
      const char *source_url;
      svn_mergeinfo_t source_mergeinfo = apr_hash_this_val(hi);
      svn_mergeinfo_t filtered_mergeinfo;
      svn_client__pathrev_t *target_pathrev;
      svn_mergeinfo_t target_history_as_mergeinfo;
      svn_error_t *err;

      svn_pool_clear(iterpool);

      source_url = svn_path_url_add_component2(source_loc->url,
                                               path_rel_to_session, iterpool);
      target_pathrev = svn_client__pathrev_join_relpath(
                         &target->loc, path_rel_to_session, iterpool);
      err = svn_client__get_history_as_mergeinfo(&target_history_as_mergeinfo,
                                                 NULL /* has_rev_zero_history */,
                                                 target_pathrev,
                                                 target->loc.rev,
                                                 SVN_INVALID_REVNUM,
                                                 target_ra_session,
                                                 ctx, iterpool);
      if (err)
        {
          if (err->apr_err == SVN_ERR_FS_NOT_FOUND
              || err->apr_err == SVN_ERR_RA_DAV_REQUEST_FAILED)
            {
              /* This path with explicit mergeinfo in the source doesn't
                 exist on the target. */
              svn_error_clear(err);
              err = NULL;
            }
          else
            {
              return svn_error_trace(err);
            }
        }
      else
        {
          svn_client__pathrev_t *pathrev;

          SVN_ERR(find_youngest_merged_rev(youngest_merged_rev,
                                           target_history_as_mergeinfo,
                                           source_mergeinfo,
                                           iterpool));

          /* Use scratch_pool rather than iterpool because filtered_mergeinfo
             is going into new_catalog below and needs to last to the end of
             this function. */
          /* ### Why looking at SOURCE_url at TARGET_rev? */
          SVN_ERR(svn_client__pathrev_create_with_session(
                    &pathrev, source_ra_session, target->loc.rev, source_url,
                    iterpool));
          SVN_ERR(find_unmerged_mergeinfo_subroutine(
                    &filtered_mergeinfo, target_history_as_mergeinfo,
                    source_mergeinfo, pathrev,
                    source_ra_session, ctx, scratch_pool, iterpool));
          if (apr_hash_count(filtered_mergeinfo))
            svn_hash_sets(new_catalog,
                          apr_pstrdup(scratch_pool, source_path),
                          filtered_mergeinfo);
        }
    }

  /* Limit new_catalog to the youngest revisions previously merged from
     the target to the source. */
  if (SVN_IS_VALID_REVNUM(*youngest_merged_rev))
    SVN_ERR(svn_mergeinfo__filter_catalog_by_ranges(&new_catalog,
                                                    new_catalog,
                                                    *youngest_merged_rev,
                                                    0, /* No oldest bound. */
                                                    TRUE,
                                                    scratch_pool,
                                                    scratch_pool));

  /* Make a shiny new copy before blowing away all the temporary pools. */
  *unmerged_to_source_catalog = svn_mergeinfo_catalog_dup(new_catalog,
                                                          result_pool);
  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}