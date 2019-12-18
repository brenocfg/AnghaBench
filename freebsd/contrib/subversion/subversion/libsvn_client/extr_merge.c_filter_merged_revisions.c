#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_24__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_25__ {TYPE_1__* remaining_ranges; int /*<<< orphan*/  implicit_mergeinfo; } ;
typedef  TYPE_2__ svn_client__merge_path_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ensure_implicit_mergeinfo (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pool ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_rangelist__initialize (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_diff (TYPE_1__**,TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_intersect (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_merge2 (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_remove (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_reverse (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
filter_merged_revisions(svn_client__merge_path_t *parent,
                        svn_client__merge_path_t *child,
                        const char *mergeinfo_path,
                        svn_rangelist_t *target_rangelist,
                        svn_revnum_t revision1,
                        svn_revnum_t revision2,
                        svn_boolean_t child_inherits_implicit,
                        svn_ra_session_t *ra_session,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_rangelist_t *requested_rangelist,
    *target_implicit_rangelist, *explicit_rangelist;

  /* Convert REVISION1 and REVISION2 to a rangelist.

     Note: Talking about a requested merge range's inheritability
     doesn't make much sense, but as we are using svn_merge_range_t
     to describe it we need to pick *something*.  Since all the
     rangelist manipulations in this function either don't consider
     inheritance by default or we are requesting that they don't (i.e.
     svn_rangelist_remove and svn_rangelist_intersect) then we could
     set the inheritability as FALSE, it won't matter either way. */
  requested_rangelist = svn_rangelist__initialize(revision1, revision2,
                                                  TRUE, scratch_pool);

  /* Now filter out revisions that have already been merged to CHILD. */

  if (revision1 > revision2) /* This is a reverse merge. */
    {
      svn_rangelist_t *added_rangelist, *deleted_rangelist;

      /* The revert range and will need to be reversed for
         our svn_rangelist_* APIs to work properly. */
      SVN_ERR(svn_rangelist_reverse(requested_rangelist, scratch_pool));

      /* Set EXPLICIT_RANGELIST to the list of source-range revs that are
         already recorded as merged to target. */
      if (target_rangelist)
        {
          /* Return the intersection of the revs which are both already
             represented by CHILD's explicit or inherited mergeinfo.

             We don't consider inheritance when determining intersecting
             ranges.  If we *did* consider inheritance, then our calculation
             would be wrong.  For example, if the CHILD->REMAINING_RANGES is
             5:3 and TARGET_RANGELIST is r5* (non-inheritable) then the
             intersection would be r4.  And that would be wrong as we clearly
             want to reverse merge both r4 and r5 in this case.  Ignoring the
             ranges' inheritance results in an intersection of r4-5.

             You might be wondering about CHILD's children, doesn't the above
             imply that we will reverse merge r4-5 from them?  Nope, this is
             safe to do because any path whose parent has non-inheritable
             ranges is always considered a subtree with differing mergeinfo
             even if that path has no explicit mergeinfo prior to the
             merge -- See condition 3 in the doc string for
             merge.c:get_mergeinfo_paths(). */
          SVN_ERR(svn_rangelist_intersect(&explicit_rangelist,
                                          target_rangelist,
                                          requested_rangelist,
                                          FALSE, scratch_pool));
        }
      else
        {
          explicit_rangelist =
            apr_array_make(result_pool, 0, sizeof(svn_merge_range_t *));
        }

      /* Was any part of the requested reverse merge not accounted for in
         CHILD's explicit or inherited mergeinfo? */
      SVN_ERR(svn_rangelist_diff(&deleted_rangelist, &added_rangelist,
                                 requested_rangelist, explicit_rangelist,
                                 FALSE, scratch_pool));

      if (deleted_rangelist->nelts == 0)
        {
          /* The whole of REVISION1:REVISION2 was represented in CHILD's
             explicit/inherited mergeinfo, allocate CHILD's remaining
             ranges in POOL and then we are done. */
          SVN_ERR(svn_rangelist_reverse(requested_rangelist, scratch_pool));
          child->remaining_ranges = svn_rangelist_dup(requested_rangelist,
                                                      result_pool);
        }
      else /* We need to check CHILD's implicit mergeinfo. */
        {
          svn_rangelist_t *implicit_rangelist;

          SVN_ERR(ensure_implicit_mergeinfo(parent,
                                            child,
                                            child_inherits_implicit,
                                            revision1,
                                            revision2,
                                            ra_session,
                                            ctx,
                                            result_pool,
                                            scratch_pool));

          target_implicit_rangelist = svn_hash_gets(child->implicit_mergeinfo,
                                                    mergeinfo_path);

          if (target_implicit_rangelist)
            SVN_ERR(svn_rangelist_intersect(&implicit_rangelist,
                                            target_implicit_rangelist,
                                            requested_rangelist,
                                            FALSE, scratch_pool));
          else
            implicit_rangelist = apr_array_make(scratch_pool, 0,
                                                sizeof(svn_merge_range_t *));

          SVN_ERR(svn_rangelist_merge2(implicit_rangelist,
                                       explicit_rangelist, scratch_pool,
                                       scratch_pool));
          SVN_ERR(svn_rangelist_reverse(implicit_rangelist, scratch_pool));
          child->remaining_ranges = svn_rangelist_dup(implicit_rangelist,
                                                      result_pool);
        }
    }
  else /* This is a forward merge */
    {
      /* Set EXPLICIT_RANGELIST to the list of source-range revs that are
         NOT already recorded as merged to target. */
      if (target_rangelist)
        {
          /* See earlier comment preceding svn_rangelist_intersect() for
             why we don't consider inheritance here. */
          SVN_ERR(svn_rangelist_remove(&explicit_rangelist,
                                       target_rangelist,
                                       requested_rangelist, FALSE,
                                       scratch_pool));
        }
      else
        {
          explicit_rangelist = svn_rangelist_dup(requested_rangelist,
                                                 scratch_pool);
        }

      if (explicit_rangelist->nelts == 0)
        {
          child->remaining_ranges =
            apr_array_make(result_pool, 0, sizeof(svn_merge_range_t *));
        }
      else
/* ### TODO:  Which evil shall we choose?
   ###
   ### If we allow all forward-merges not already found in recorded
   ### mergeinfo, we destroy the ability to, say, merge the whole of a
   ### branch to the trunk while automatically ignoring the revisions
   ### common to both.  That's bad.
   ###
   ### If we allow only forward-merges not found in either recorded
   ### mergeinfo or implicit mergeinfo (natural history), then the
   ### previous scenario works great, but we can't reverse-merge a
   ### previous change made to our line of history and then remake it
   ### (because the reverse-merge will leave no mergeinfo trace, and
   ### the remake-it attempt will still find the original change in
   ### natural mergeinfo.  But you know, that we happen to use 'merge'
   ### for revision undoing is somewhat unnatural anyway, so I'm
   ### finding myself having little interest in caring too much about
   ### this.  That said, if we had a way of storing reverse merge
   ### ranges, we'd be in good shape either way.
*/
#ifdef SVN_MERGE__ALLOW_ALL_FORWARD_MERGES_FROM_SELF
        {
          /* ### Don't consider implicit mergeinfo. */
          child->remaining_ranges = svn_rangelist_dup(explicit_rangelist,
                                                      pool);
        }
#else
        {
          /* Based on CHILD's TARGET_MERGEINFO there are ranges to merge.
             Check CHILD's implicit mergeinfo to see if these remaining
             ranges are represented there. */
          SVN_ERR(ensure_implicit_mergeinfo(parent,
                                            child,
                                            child_inherits_implicit,
                                            revision1,
                                            revision2,
                                            ra_session,
                                            ctx,
                                            result_pool,
                                            scratch_pool));

          target_implicit_rangelist = svn_hash_gets(child->implicit_mergeinfo,
                                                    mergeinfo_path);
          if (target_implicit_rangelist)
            SVN_ERR(svn_rangelist_remove(&(child->remaining_ranges),
                                         target_implicit_rangelist,
                                         explicit_rangelist,
                                         FALSE, result_pool));
          else
            child->remaining_ranges = svn_rangelist_dup(explicit_rangelist,
                                                        result_pool);
        }
#endif
    }

  return SVN_NO_ERROR;
}