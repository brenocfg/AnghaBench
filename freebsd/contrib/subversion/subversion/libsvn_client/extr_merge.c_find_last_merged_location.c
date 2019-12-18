#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_18__ {scalar_t__ number; } ;
struct TYPE_20__ {TYPE_1__ value; void* kind; } ;
typedef  TYPE_3__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_21__ {scalar_t__ rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
struct TYPE_22__ {TYPE_2__* tip; } ;
typedef  TYPE_5__ branch_history_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/  url; scalar_t__ rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  branch_history_get_endpoints (int /*<<< orphan*/ *,TYPE_4__**,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  branch_history_intersect_range (TYPE_5__**,TYPE_5__ const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  operative_rev_receiver ; 
 int /*<<< orphan*/  short_circuit_mergeinfo_log (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_opt_revision_number ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_last_merged_location(svn_client__pathrev_t **base_p,
                          svn_client__pathrev_t *yca,
                          const branch_history_t *source_branch,
                          svn_client__pathrev_t *target,
                          svn_client_ctx_t *ctx,
                          svn_ra_session_t *ra_session,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  svn_opt_revision_t source_peg_rev, source_start_rev, source_end_rev,
    target_opt_rev;
  svn_revnum_t youngest_merged_rev = SVN_INVALID_REVNUM;
  svn_mergeinfo_catalog_t target_mergeinfo_cat = NULL;

  /* Using a local subpool for 'target_mergeinfo_cat' can make a big
     reduction in overall memory usage. */
  apr_pool_t *tmic_pool = svn_pool_create(scratch_pool);

  source_peg_rev.kind = svn_opt_revision_number;
  source_peg_rev.value.number = source_branch->tip->rev;
  source_start_rev.kind = svn_opt_revision_number;
  source_start_rev.value.number = yca->rev;
  source_end_rev.kind = svn_opt_revision_number;
  source_end_rev.value.number = source_branch->tip->rev;
  target_opt_rev.kind = svn_opt_revision_number;
  target_opt_rev.value.number = target->rev;

  /* Find the youngest revision fully merged from SOURCE_BRANCH to TARGET,
     if such a revision exists. */
  SVN_ERR(short_circuit_mergeinfo_log(&target_mergeinfo_cat,
                                      TRUE, /* Find merged */
                                      target->url, &target_opt_rev,
                                      source_branch->tip->url,
                                      &source_peg_rev,
                                      &source_end_rev, &source_start_rev,
                                      operative_rev_receiver,
                                      &youngest_merged_rev,
                                      ctx, ra_session,
                                      tmic_pool, tmic_pool));

  if (!SVN_IS_VALID_REVNUM(youngest_merged_rev))
    {
      /* No revisions have been completely merged from SOURCE_BRANCH to
         TARGET so the base for the next merge is the YCA. */
      *base_p = yca;
    }
  else
    {
      /* One or more revisions have already been completely merged from
         SOURCE_BRANCH to TARGET, now find the oldest revision, older
         than the youngest merged revision, which is still eligible to
         be merged, if such exists. */
      branch_history_t *contiguous_source;
      svn_revnum_t base_rev;
      svn_revnum_t oldest_eligible_rev = SVN_INVALID_REVNUM;

      /* If the only revisions eligible are younger than the youngest merged
         revision we can simply assume that the youngest eligible revision
         is the youngest merged revision.  Obviously this may not be true!
         The revisions between the youngest merged revision and the tip of
         the branch may have several inoperative revisions -- they may *all*
         be inoperative revisions!  But for the purpose of this function
         (i.e. finding the youngest revision after the YCA where all revs have
         been merged) that doesn't matter. */
      source_end_rev.value.number = youngest_merged_rev;
      SVN_ERR(short_circuit_mergeinfo_log(&target_mergeinfo_cat,
                                          FALSE, /* Find eligible */
                                          target->url, &target_opt_rev,
                                          source_branch->tip->url,
                                          &source_peg_rev,
                                          &source_start_rev, &source_end_rev,
                                          operative_rev_receiver,
                                          &oldest_eligible_rev,
                                          ctx, ra_session,
                                          tmic_pool, tmic_pool));

      /* If there are revisions eligible for merging, use the oldest one
         to calculate the base.  Otherwise there are no operative revisions
         to merge and we can simple set the base to the youngest revision
         already merged. */
      if (SVN_IS_VALID_REVNUM(oldest_eligible_rev))
        base_rev = oldest_eligible_rev - 1;
      else
        base_rev = youngest_merged_rev;

      /* Find the branch location just before the oldest eligible rev.
         (We can't just use the base revs calculated above because the branch
         might have a gap there.) */
      SVN_ERR(branch_history_intersect_range(&contiguous_source,
                                             source_branch, yca->rev,
                                             base_rev,
                                             scratch_pool, scratch_pool));
      SVN_ERR(branch_history_get_endpoints(NULL, base_p, contiguous_source,
                                           result_pool, scratch_pool));
    }

  svn_pool_destroy(tmic_pool);
  return SVN_NO_ERROR;
}