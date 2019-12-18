#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_23__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
struct TYPE_37__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_38__ {scalar_t__ url; scalar_t__ repos_root_url; scalar_t__ rev; } ;
typedef  TYPE_3__ svn_client__pathrev_t ;
struct TYPE_36__ {scalar_t__ url; scalar_t__ repos_root_url; } ;
struct TYPE_39__ {TYPE_23__ loc; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_4__ merge_target_t ;
struct TYPE_40__ {int ancestral; TYPE_3__ const* loc2; TYPE_3__* loc1; } ;
typedef  TYPE_5__ merge_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_CLIENT_INVALID_MERGEINFO_NO_MERGETRACKING ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_NOT_READY_TO_MERGE ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* calculate_left_hand_side (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__ const*,int /*<<< orphan*/ *,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* find_unsynced_ranges (TYPE_3__ const*,TYPE_23__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* get_wc_explicit_mergeinfo_catalog (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* merge_source_dup (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_url_is (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 TYPE_2__* svn_client__get_youngest_common_ancestor (TYPE_3__**,TYPE_3__ const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__pathrev_dup (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* svn_error_quick_wrap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_mergeinfo__catalog_to_formatted_string (TYPE_1__**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_reparent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_reintegrate_merge(merge_source_t **source_p,
                       svn_client__pathrev_t **yc_ancestor_p,
                       svn_ra_session_t *source_ra_session,
                       const svn_client__pathrev_t *source_loc,
                       svn_ra_session_t *target_ra_session,
                       const merge_target_t *target,
                       svn_client_ctx_t *ctx,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_client__pathrev_t *yc_ancestor;
  svn_client__pathrev_t *loc1;
  merge_source_t source;
  svn_mergeinfo_catalog_t unmerged_to_source_mergeinfo_catalog;
  svn_mergeinfo_catalog_t merged_to_source_mergeinfo_catalog;
  svn_error_t *err;
  apr_hash_t *subtrees_with_mergeinfo;

  assert(session_url_is(source_ra_session, source_loc->url, scratch_pool));
  assert(session_url_is(target_ra_session, target->loc.url, scratch_pool));

  /* As the WC tree is "pure", use its last-updated-to revision as
     the default revision for the left side of our merge, since that's
     what the repository sub-tree is required to be up to date with
     (with regard to the WC). */
  /* ### Bogus/obsolete comment? */

  /* Can't reintegrate to or from the root of the repository. */
  if (strcmp(source_loc->url, source_loc->repos_root_url) == 0
      || strcmp(target->loc.url, target->loc.repos_root_url) == 0)
    return svn_error_createf(SVN_ERR_CLIENT_NOT_READY_TO_MERGE, NULL,
                             _("Neither the reintegrate source nor target "
                               "can be the root of the repository"));

  /* Find all the subtrees in TARGET_WCPATH that have explicit mergeinfo. */
  err = get_wc_explicit_mergeinfo_catalog(&subtrees_with_mergeinfo,
                                          target->abspath, svn_depth_infinity,
                                          ctx, scratch_pool, scratch_pool);
  /* Issue #3896: If invalid mergeinfo in the reintegrate target
     prevents us from proceeding, then raise the best error possible. */
  if (err && err->apr_err == SVN_ERR_CLIENT_INVALID_MERGEINFO_NO_MERGETRACKING)
    err = svn_error_quick_wrap(err, _("Reintegrate merge not possible"));
  SVN_ERR(err);

  SVN_ERR(calculate_left_hand_side(&loc1,
                                   &merged_to_source_mergeinfo_catalog,
                                   &unmerged_to_source_mergeinfo_catalog,
                                   target,
                                   subtrees_with_mergeinfo,
                                   source_loc,
                                   source_ra_session,
                                   target_ra_session,
                                   ctx,
                                   scratch_pool, scratch_pool));

  /* Did calculate_left_hand_side() decide that there was no merge to
     be performed here?  */
  if (! loc1)
    {
      if (source_p)
        *source_p = NULL;
      if (yc_ancestor_p)
        *yc_ancestor_p = NULL;
      return SVN_NO_ERROR;
    }

  source.loc1 = loc1;
  source.loc2 = source_loc;

  /* If the target was moved after the source was branched from it,
     it is possible that the left URL differs from the target's current
     URL.  If so, then adjust TARGET_RA_SESSION to point to the old URL. */
  if (strcmp(source.loc1->url, target->loc.url))
    SVN_ERR(svn_ra_reparent(target_ra_session, source.loc1->url, scratch_pool));

  SVN_ERR(svn_client__get_youngest_common_ancestor(
            &yc_ancestor, source.loc2, source.loc1, target_ra_session,
            ctx, scratch_pool, scratch_pool));

  if (! yc_ancestor)
    return svn_error_createf(SVN_ERR_CLIENT_NOT_READY_TO_MERGE, NULL,
                             _("'%s@%ld' must be ancestrally related to "
                               "'%s@%ld'"),
                             source.loc1->url, source.loc1->rev,
                             source.loc2->url, source.loc2->rev);

  /* The source side of a reintegrate merge is not 'ancestral', except in
   * the degenerate case where source == YCA. */
  source.ancestral = (loc1->rev == yc_ancestor->rev);

  if (source.loc1->rev > yc_ancestor->rev)
    {
      /* Have we actually merged anything to the source from the
         target?  If so, make sure we've merged a contiguous
         prefix. */
      svn_mergeinfo_catalog_t final_unmerged_catalog = apr_hash_make(scratch_pool);

      SVN_ERR(find_unsynced_ranges(source_loc, &target->loc,
                                   unmerged_to_source_mergeinfo_catalog,
                                   merged_to_source_mergeinfo_catalog,
                                   final_unmerged_catalog,
                                   target_ra_session, scratch_pool,
                                   scratch_pool));

      if (apr_hash_count(final_unmerged_catalog))
        {
          svn_string_t *source_mergeinfo_cat_string;

          SVN_ERR(svn_mergeinfo__catalog_to_formatted_string(
            &source_mergeinfo_cat_string,
            final_unmerged_catalog,
            "  ", _("    Missing ranges: "), scratch_pool));
          return svn_error_createf(SVN_ERR_CLIENT_NOT_READY_TO_MERGE,
                                   NULL,
                                   _("Reintegrate can only be used if "
                                     "revisions %ld through %ld were "
                                     "previously merged from %s to the "
                                     "reintegrate source, but this is "
                                     "not the case:\n%s"),
                                   yc_ancestor->rev + 1, source.loc2->rev,
                                   target->loc.url,
                                   source_mergeinfo_cat_string->data);
        }
    }

  /* Left side: trunk@youngest-trunk-rev-merged-to-branch-at-specified-peg-rev
   * Right side: branch@specified-peg-revision */
  if (source_p)
    *source_p = merge_source_dup(&source, result_pool);

  if (yc_ancestor_p)
    *yc_ancestor_p = svn_client__pathrev_dup(yc_ancestor, result_pool);
  return SVN_NO_ERROR;
}