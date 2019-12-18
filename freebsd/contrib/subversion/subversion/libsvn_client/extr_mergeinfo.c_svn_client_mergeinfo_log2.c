#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_client__mergeinfo_log (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_client_mergeinfo_log2(svn_boolean_t finding_merged,
                          const char *target_path_or_url,
                          const svn_opt_revision_t *target_peg_revision,
                          const char *source_path_or_url,
                          const svn_opt_revision_t *source_peg_revision,
                          const svn_opt_revision_t *source_start_revision,
                          const svn_opt_revision_t *source_end_revision,
                          svn_log_entry_receiver_t log_receiver,
                          void *log_receiver_baton,
                          svn_boolean_t discover_changed_paths,
                          svn_depth_t depth,
                          const apr_array_header_t *revprops,
                          svn_client_ctx_t *ctx,
                          apr_pool_t *scratch_pool)
{
  return svn_error_trace(
         svn_client__mergeinfo_log(finding_merged, target_path_or_url,
                                   target_peg_revision, NULL,
                                   source_path_or_url, source_peg_revision,
                                   source_start_revision, source_end_revision,
                                   log_receiver, log_receiver_baton,
                                   discover_changed_paths, depth, revprops,
                                   ctx, NULL,
                                   scratch_pool, scratch_pool));
}