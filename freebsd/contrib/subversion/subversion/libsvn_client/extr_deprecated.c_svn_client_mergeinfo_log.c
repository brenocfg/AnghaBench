#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_client_mergeinfo_log2 (int /*<<< orphan*/ ,char const*,TYPE_1__ const*,char const*,TYPE_1__ const*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_opt_revision_unspecified ; 

svn_error_t *
svn_client_mergeinfo_log(svn_boolean_t finding_merged,
                         const char *target_path_or_url,
                         const svn_opt_revision_t *target_peg_revision,
                         const char *source_path_or_url,
                         const svn_opt_revision_t *source_peg_revision,
                         svn_log_entry_receiver_t receiver,
                         void *receiver_baton,
                         svn_boolean_t discover_changed_paths,
                         svn_depth_t depth,
                         const apr_array_header_t *revprops,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *scratch_pool)
{
  svn_opt_revision_t start_revision, end_revision;

  start_revision.kind = svn_opt_revision_unspecified;
  end_revision.kind = svn_opt_revision_unspecified;

  return svn_client_mergeinfo_log2(finding_merged,
                                   target_path_or_url, target_peg_revision,
                                   source_path_or_url, source_peg_revision,
                                   &start_revision, &end_revision,
                                   receiver, receiver_baton,
                                   discover_changed_paths, depth, revprops,
                                   ctx, scratch_pool);
}