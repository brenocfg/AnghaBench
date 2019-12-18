#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_client__conflict_report_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  merge_target_t ;
struct TYPE_4__ {void* ancestral; } ;
typedef  TYPE_1__ merge_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * find_reintegrate_merge (TYPE_1__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * merge_cousins_and_supplement_mergeinfo (int /*<<< orphan*/ **,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_reintegrate_source_and_target (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
merge_reintegrate_locked(svn_client__conflict_report_t **conflict_report,
                         const char *source_path_or_url,
                         const svn_opt_revision_t *source_peg_revision,
                         const char *target_abspath,
                         svn_boolean_t diff_ignore_ancestry,
                         svn_boolean_t dry_run,
                         const apr_array_header_t *merge_options,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_ra_session_t *target_ra_session, *source_ra_session;
  merge_target_t *target;
  svn_client__pathrev_t *source_loc;
  merge_source_t *source;
  svn_client__pathrev_t *yc_ancestor;
  svn_boolean_t use_sleep = FALSE;
  svn_error_t *err;

  SVN_ERR(open_reintegrate_source_and_target(
            &source_ra_session, &source_loc, &target_ra_session, &target,
            source_path_or_url, source_peg_revision, target_abspath,
            ctx, scratch_pool, scratch_pool));

  SVN_ERR(find_reintegrate_merge(&source, &yc_ancestor,
                                 source_ra_session, source_loc,
                                 target_ra_session, target,
                                 ctx, scratch_pool, scratch_pool));

  if (! source)
    {
      *conflict_report = NULL;
      return SVN_NO_ERROR;
    }

  /* Do the real merge! */
  /* ### TODO(reint): Make sure that one isn't the same line ancestor
     ### of the other (what's erroneously referred to as "ancestrally
     ### related" in this source file).  For now, we just say the source
     ### isn't "ancestral" even if it is (in the degenerate case where
     ### source-left equals YCA). */
  source->ancestral = FALSE;
  err = merge_cousins_and_supplement_mergeinfo(conflict_report,
                                               &use_sleep,
                                               target,
                                               target_ra_session,
                                               source_ra_session,
                                               source, yc_ancestor,
                                               TRUE /* same_repos */,
                                               svn_depth_infinity,
                                               diff_ignore_ancestry,
                                               FALSE /* force_delete */,
                                               FALSE /* record_only */,
                                               dry_run,
                                               merge_options,
                                               ctx,
                                               result_pool, scratch_pool);

  if (use_sleep)
    svn_io_sleep_for_timestamps(target_abspath, scratch_pool);

  SVN_ERR(err);
  return SVN_NO_ERROR;
}