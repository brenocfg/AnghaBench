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
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_client__get_history_as_mergeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_merge2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_remove2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_unmerged_mergeinfo_subroutine(svn_mergeinfo_t *filtered_mergeinfo_p,
                                   svn_mergeinfo_t target_history_as_mergeinfo,
                                   svn_mergeinfo_t source_mergeinfo,
                                   const svn_client__pathrev_t *source_pathrev,
                                   svn_ra_session_t *source_ra_session,
                                   svn_client_ctx_t *ctx,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  svn_mergeinfo_t source_history_as_mergeinfo;

  /* Get the source path's natural history and merge it into source
     path's explicit or inherited mergeinfo. */
  SVN_ERR(svn_client__get_history_as_mergeinfo(
            &source_history_as_mergeinfo, NULL /* has_rev_zero_history */,
            source_pathrev, source_pathrev->rev, SVN_INVALID_REVNUM,
            source_ra_session, ctx, scratch_pool));
  SVN_ERR(svn_mergeinfo_merge2(source_mergeinfo,
                               source_history_as_mergeinfo,
                               scratch_pool, scratch_pool));

  /* Now source_mergeinfo represents everything we know about
     source_path's history.  Now we need to know what part, if any, of the
     corresponding target's history is *not* part of source_path's total
     history; because it is neither shared history nor was it ever merged
     from the target to the source. */
  SVN_ERR(svn_mergeinfo_remove2(filtered_mergeinfo_p,
                                source_mergeinfo,
                                target_history_as_mergeinfo, TRUE,
                                result_pool, scratch_pool));
  return SVN_NO_ERROR;
}