#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_12__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__conflict_report_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ensure_wc_path_has_repo_revision (char const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_target_and_lock_abspath (char const**,char const**,char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__make_merge_conflict_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__merge_locked (int /*<<< orphan*/ **,char const*,TYPE_1__ const*,char const*,TYPE_1__ const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_merge5(const char *source1,
                  const svn_opt_revision_t *revision1,
                  const char *source2,
                  const svn_opt_revision_t *revision2,
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

  /* Sanity check our input -- we require specified revisions,
   * and either 2 paths or 2 URLs. */
  if ((revision1->kind == svn_opt_revision_unspecified)
      || (revision2->kind == svn_opt_revision_unspecified))
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                            _("Not all required revisions are specified"));
  if (svn_path_is_url(source1) != svn_path_is_url(source2))
    return svn_error_create(SVN_ERR_ILLEGAL_TARGET, NULL,
                            _("Merge sources must both be "
                              "either paths or URLs"));
  /* A WC path must be used with a repository revision, as we can't
   * (currently) use the WC itself as a source, we can only read the URL
   * from it and use that. */
  SVN_ERR(ensure_wc_path_has_repo_revision(source1, revision1, pool));
  SVN_ERR(ensure_wc_path_has_repo_revision(source2, revision2, pool));

  SVN_ERR(get_target_and_lock_abspath(&target_abspath, &lock_abspath,
                                      target_wcpath, ctx, pool));

  if (!dry_run)
    SVN_WC__CALL_WITH_WRITE_LOCK(
      svn_client__merge_locked(&conflict_report,
                               source1, revision1, source2, revision2,
                               target_abspath, depth, ignore_mergeinfo,
                               diff_ignore_ancestry,
                               force_delete, record_only, dry_run,
                               allow_mixed_rev, merge_options, ctx, pool, pool),
      ctx->wc_ctx, lock_abspath, FALSE /* lock_anchor */, pool);
  else
    SVN_ERR(svn_client__merge_locked(&conflict_report,
                                     source1, revision1, source2, revision2,
                                     target_abspath, depth, ignore_mergeinfo,
                                     diff_ignore_ancestry,
                                     force_delete, record_only, dry_run,
                                     allow_mixed_rev, merge_options, ctx, pool,
                                     pool));

  SVN_ERR(svn_client__make_merge_conflict_error(conflict_report, pool));
  return SVN_NO_ERROR;
}