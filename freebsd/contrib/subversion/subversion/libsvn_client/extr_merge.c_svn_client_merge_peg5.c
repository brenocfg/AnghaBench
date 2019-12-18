#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_13__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__conflict_report_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  automatic_merge_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  client_find_automatic_merge (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_automatic_merge_locked (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_target_and_lock_abspath (char const**,char const**,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_peg_locked (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/  const*,TYPE_2__ const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__make_merge_conflict_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_client_merge_peg5(const char *source_path_or_url,
                      const apr_array_header_t *ranges_to_merge,
                      const svn_opt_revision_t *source_peg_revision,
                      const char *target_wcpath,
                      svn_depth_t depth,
                      svn_boolean_t ignore_mergeinfo,
                      svn_boolean_t diff_ignore_ancestry,
                      svn_boolean_t force_delete,
                      svn_boolean_t record_only,
                      svn_boolean_t dry_run,
                      svn_boolean_t allow_mixed_rev,
                      const apr_array_header_t *merge_options,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *pool)
{
  const char *target_abspath, *lock_abspath;
  svn_client__conflict_report_t *conflict_report;

  /* No ranges to merge?  No problem. */
  if (ranges_to_merge != NULL && ranges_to_merge->nelts == 0)
    return SVN_NO_ERROR;

  SVN_ERR(get_target_and_lock_abspath(&target_abspath, &lock_abspath,
                                      target_wcpath, ctx, pool));

  /* Do an automatic merge if no revision ranges are specified. */
  if (ranges_to_merge == NULL)
    {
      automatic_merge_t *merge;

      if (ignore_mergeinfo)
        return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                                _("Cannot merge automatically while "
                                  "ignoring mergeinfo"));

      /* Find the details of the merge needed. */
      SVN_ERR(client_find_automatic_merge(
                                    &merge,
                                    source_path_or_url, source_peg_revision,
                                    target_abspath,
                                    allow_mixed_rev,
                                    TRUE /*allow_local_mods*/,
                                    TRUE /*allow_switched_subtrees*/,
                                    ctx, pool, pool));

      if (!dry_run)
        SVN_WC__CALL_WITH_WRITE_LOCK(
          do_automatic_merge_locked(&conflict_report,
                                    merge,
                                    target_abspath, depth,
                                    diff_ignore_ancestry,
                                    force_delete, record_only, dry_run,
                                    merge_options, ctx, pool, pool),
          ctx->wc_ctx, lock_abspath, FALSE /* lock_anchor */, pool);
      else
        SVN_ERR(do_automatic_merge_locked(&conflict_report,
                                    merge,
                                    target_abspath, depth,
                                    diff_ignore_ancestry,
                                    force_delete, record_only, dry_run,
                                    merge_options, ctx, pool, pool));
    }
  else if (!dry_run)
    SVN_WC__CALL_WITH_WRITE_LOCK(
      merge_peg_locked(&conflict_report,
                       source_path_or_url, source_peg_revision,
                       ranges_to_merge,
                       target_abspath, depth, ignore_mergeinfo,
                       diff_ignore_ancestry,
                       force_delete, record_only, dry_run,
                       allow_mixed_rev, merge_options, ctx, pool, pool),
      ctx->wc_ctx, lock_abspath, FALSE /* lock_anchor */, pool);
  else
    SVN_ERR(merge_peg_locked(&conflict_report,
                       source_path_or_url, source_peg_revision,
                       ranges_to_merge,
                       target_abspath, depth, ignore_mergeinfo,
                       diff_ignore_ancestry,
                       force_delete, record_only, dry_run,
                       allow_mixed_rev, merge_options, ctx, pool, pool));

  SVN_ERR(svn_client__make_merge_conflict_error(conflict_report, pool));
  return SVN_NO_ERROR;
}