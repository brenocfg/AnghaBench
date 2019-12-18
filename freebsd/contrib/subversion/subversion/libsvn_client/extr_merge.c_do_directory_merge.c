#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client__merge_path_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  single_range_conflict_report_t ;
typedef  int /*<<< orphan*/  merge_source_t ;
struct TYPE_7__ {int /*<<< orphan*/ * nodes_with_mergeinfo; } ;
struct TYPE_8__ {TYPE_1__ notify_begin; } ;
typedef  TYPE_2__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ HONOR_MERGEINFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  do_mergeinfo_aware_dir_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_mergeinfo_unaware_dir_merge (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_directory_merge(svn_mergeinfo_catalog_t result_catalog,
                   single_range_conflict_report_t **conflict_report,
                   const merge_source_t *source,
                   const char *target_abspath,
                   const svn_diff_tree_processor_t *processor,
                   svn_depth_t depth,
                   svn_boolean_t squelch_mergeinfo_notifications,
                   merge_cmd_baton_t *merge_b,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  apr_array_header_t *children_with_mergeinfo;

  /* Initialize CHILDREN_WITH_MERGEINFO. See the comment
     'THE CHILDREN_WITH_MERGEINFO ARRAY' at the start of this file. */
  children_with_mergeinfo =
    apr_array_make(scratch_pool, 16, sizeof(svn_client__merge_path_t *));

  /* And make it read-only accessible from the baton */
  merge_b->notify_begin.nodes_with_mergeinfo = children_with_mergeinfo;

  /* If we are not honoring mergeinfo we can skip right to the
     business of merging changes! */
  if (HONOR_MERGEINFO(merge_b))
    SVN_ERR(do_mergeinfo_aware_dir_merge(result_catalog, conflict_report,
                                         source, target_abspath,
                                         children_with_mergeinfo,
                                         processor, depth,
                                         squelch_mergeinfo_notifications,
                                         merge_b, result_pool, scratch_pool));
  else
    SVN_ERR(do_mergeinfo_unaware_dir_merge(conflict_report,
                                           source, target_abspath,
                                           children_with_mergeinfo,
                                           processor, depth,
                                           merge_b, result_pool, scratch_pool));

  merge_b->notify_begin.nodes_with_mergeinfo = NULL;

  return SVN_NO_ERROR;
}