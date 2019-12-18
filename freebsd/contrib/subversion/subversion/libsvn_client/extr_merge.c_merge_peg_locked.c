#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_client__conflict_report_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  loc; } ;
typedef  TYPE_1__ merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * do_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ getenv (char*) ; 
 scalar_t__ is_same_repos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * normalize_merge_sources (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_target_wc (TYPE_1__**,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__merge_elements (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
merge_peg_locked(svn_client__conflict_report_t **conflict_report,
                 const char *source_path_or_url,
                 const svn_opt_revision_t *source_peg_revision,
                 const svn_rangelist_t *ranges_to_merge,
                 const char *target_abspath,
                 svn_depth_t depth,
                 svn_boolean_t ignore_mergeinfo,
                 svn_boolean_t diff_ignore_ancestry,
                 svn_boolean_t force_delete,
                 svn_boolean_t record_only,
                 svn_boolean_t dry_run,
                 svn_boolean_t allow_mixed_rev,
                 const apr_array_header_t *merge_options,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  merge_target_t *target;
  svn_client__pathrev_t *source_loc;
  apr_array_header_t *merge_sources;
  svn_ra_session_t *ra_session;
  apr_pool_t *sesspool;
  svn_boolean_t use_sleep = FALSE;
  svn_error_t *err;
  svn_boolean_t same_repos;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(target_abspath));

  SVN_ERR(open_target_wc(&target, target_abspath,
                         allow_mixed_rev, TRUE, TRUE,
                         ctx, scratch_pool, scratch_pool));

  /* Create a short lived session pool */
  sesspool = svn_pool_create(scratch_pool);

  /* Open an RA session to our source URL, and determine its root URL. */
  SVN_ERR(svn_client__ra_session_from_path2(
            &ra_session, &source_loc,
            source_path_or_url, NULL, source_peg_revision, source_peg_revision,
            ctx, sesspool));

  /* Normalize our merge sources. */
  SVN_ERR(normalize_merge_sources(&merge_sources, source_path_or_url,
                                  source_loc,
                                  ranges_to_merge, ra_session, ctx,
                                  scratch_pool, scratch_pool));

  /* Check for same_repos. */
  same_repos = is_same_repos(&target->loc, source_loc, TRUE /* strict_urls */);

  /* Do the real merge!  (We say with confidence that our merge
     sources are both ancestral and related.) */
  if (getenv("SVN_ELEMENT_MERGE")
      && same_repos
      && (depth == svn_depth_infinity || depth == svn_depth_unknown)
      && ignore_mergeinfo
      && !record_only)
    {
      err = svn_client__merge_elements(&use_sleep,
                                       merge_sources, target, ra_session,
                                       diff_ignore_ancestry, force_delete,
                                       dry_run, merge_options,
                                       ctx, result_pool, scratch_pool);
      /* ### Currently this merge just errors out on any conflicts */
      *conflict_report = NULL;
    }
  else
  err = do_merge(NULL, NULL, conflict_report, &use_sleep,
                 merge_sources, target, ra_session,
                 TRUE /*sources_related*/, same_repos, ignore_mergeinfo,
                 diff_ignore_ancestry, force_delete, dry_run,
                 record_only, NULL, FALSE, FALSE, depth, merge_options,
                 ctx, result_pool, scratch_pool);

  /* We're done with our RA session. */
  svn_pool_destroy(sesspool);

  if (use_sleep)
    svn_io_sleep_for_timestamps(target_abspath, scratch_pool);

  SVN_ERR(err);
  return SVN_NO_ERROR;
}