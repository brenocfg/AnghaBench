#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_mergeinfo_t ;
struct TYPE_26__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_27__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_28__ {scalar_t__ rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
struct TYPE_29__ {int /*<<< orphan*/  abspath; TYPE_1__* remaining_ranges; } ;
typedef  TYPE_5__ svn_client__merge_path_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_30__ {TYPE_4__* loc1; TYPE_4__* loc2; int /*<<< orphan*/  ancestral; } ;
typedef  TYPE_6__ merge_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_25__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_MERGE_UPDATE_REQUIRED ; 
 scalar_t__ SVN_ERR_CLIENT_UNRELATED_RESOURCES ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  filter_merged_revisions (TYPE_5__*,TYPE_5__*,char const*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* svn_client__pathrev_fspath (TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client__repos_location (TYPE_4__**,int /*<<< orphan*/ *,TYPE_4__*,scalar_t__,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_rangelist_remove (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_base (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_url (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
calculate_remaining_ranges(svn_client__merge_path_t *parent,
                           svn_client__merge_path_t *child,
                           const merge_source_t *source,
                           svn_mergeinfo_t target_mergeinfo,
                           const apr_array_header_t *implicit_src_gap,
                           svn_boolean_t child_inherits_implicit,
                           svn_ra_session_t *ra_session,
                           svn_client_ctx_t *ctx,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const svn_client__pathrev_t *primary_src
    = (source->loc1->rev < source->loc2->rev) ? source->loc2 : source->loc1;
  const char *mergeinfo_path = svn_client__pathrev_fspath(primary_src,
                                                          scratch_pool);
  /* Intersection of TARGET_MERGEINFO and the merge history
     described by SOURCE. */
  svn_rangelist_t *target_rangelist;
  svn_revnum_t child_base_revision;

  /* Since this function should only be called when honoring mergeinfo and
   * SOURCE adheres to the requirements noted in 'MERGEINFO MERGE SOURCE
   * NORMALIZATION', SOURCE must be 'ancestral'. */
  SVN_ERR_ASSERT(source->ancestral);

  /* Determine which of the requested ranges to consider merging... */

  /* Set TARGET_RANGELIST to the portion of TARGET_MERGEINFO that refers
     to SOURCE (excluding any gap in SOURCE): first get all ranges from
     TARGET_MERGEINFO that refer to the path of SOURCE, and then prune
     any ranges that lie in the gap in SOURCE.

     ### [JAF] In fact, that may still leave some ranges that lie entirely
     outside the range of SOURCE; it seems we don't care about that.  */
  if (target_mergeinfo)
    target_rangelist = svn_hash_gets(target_mergeinfo, mergeinfo_path);
  else
    target_rangelist = NULL;
  if (implicit_src_gap && target_rangelist)
    {
      /* Remove any mergeinfo referring to the 'gap' in SOURCE, as that
         mergeinfo doesn't really refer to SOURCE at all but instead
         refers to locations that are non-existent or on a different
         line of history.  (Issue #3242.) */
      SVN_ERR(svn_rangelist_remove(&target_rangelist,
                                   implicit_src_gap, target_rangelist,
                                   FALSE, result_pool));
    }

  /* Initialize CHILD->REMAINING_RANGES and filter out revisions already
     merged (or, in the case of reverse merges, ranges not yet merged). */
  SVN_ERR(filter_merged_revisions(parent, child, mergeinfo_path,
                                  target_rangelist,
                                  source->loc1->rev, source->loc2->rev,
                                  child_inherits_implicit,
                                  ra_session, ctx, result_pool,
                                  scratch_pool));

  /* Issue #2973 -- from the continuing series of "Why, since the advent of
     merge tracking, allowing merges into mixed rev and locally modified
     working copies isn't simple and could be considered downright evil".

     If reverse merging a range to the WC path represented by CHILD, from
     that path's own history, where the path inherits no locally modified
     mergeinfo from its WC parents (i.e. there is no uncommitted merge to
     the WC), and the path's base revision is older than the range, then
     the merge will always be a no-op.  This is because we only allow reverse
     merges of ranges in the path's explicit or natural mergeinfo and a
     reverse merge from the path's future history obviously isn't going to be
     in either, hence the no-op.

     The problem is two-fold.  First, in a mixed rev WC, the change we
     want to revert might actually be to some child of the target path
     which is at a younger base revision.  Sure, we can merge directly
     to that child or update the WC or even use --ignore-ancestry and then
     successfully run the reverse merge, but that gets to the second
     problem: Those courses of action are not very obvious.  Before 1.5 if
     a user committed a change that didn't touch the commit target, then
     immediately decided to revert that change via a reverse merge it would
     just DTRT.  But with the advent of merge tracking the user gets a no-op.

     So in the name of user friendliness, return an error suggesting a helpful
     course of action.
  */
  SVN_ERR(svn_wc__node_get_base(NULL, &child_base_revision,
                                NULL, NULL, NULL, NULL,
                                ctx->wc_ctx, child->abspath,
                                TRUE /* ignore_enoent */,
                                scratch_pool, scratch_pool));
  /* If CHILD has no base revision then it hasn't been committed yet, so it
     can't have any "future" history. */
  if (SVN_IS_VALID_REVNUM(child_base_revision)
      && ((child->remaining_ranges)->nelts == 0) /* Inoperative merge */
      && (source->loc2->rev < source->loc1->rev)     /* Reverse merge */
      && (child_base_revision <= source->loc2->rev))  /* From CHILD's future */
    {
      /* Hmmm, an inoperative reverse merge from the "future".  If it is
         from our own future return a helpful error. */
      svn_error_t *err;
      svn_client__pathrev_t *start_loc;

      err = svn_client__repos_location(&start_loc,
                                       ra_session,
                                       source->loc1,
                                       child_base_revision,
                                       ctx, scratch_pool, scratch_pool);
      if (err)
        {
          if (err->apr_err == SVN_ERR_FS_NOT_FOUND
              || err->apr_err == SVN_ERR_CLIENT_UNRELATED_RESOURCES)
            svn_error_clear(err);
          else
            return svn_error_trace(err);
        }
      else
        {
          const char *url;

          SVN_ERR(svn_wc__node_get_url(&url, ctx->wc_ctx, child->abspath,
                                       scratch_pool, scratch_pool));
          if (strcmp(start_loc->url, url) == 0)
            return svn_error_create(SVN_ERR_CLIENT_MERGE_UPDATE_REQUIRED, NULL,
                                    _("Cannot reverse-merge a range from a "
                                      "path's own future history; try "
                                      "updating first"));
        }
    }

  return SVN_NO_ERROR;
}