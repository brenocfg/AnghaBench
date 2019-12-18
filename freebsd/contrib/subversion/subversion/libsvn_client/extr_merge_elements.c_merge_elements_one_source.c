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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  merge_target_t ;
typedef  int /*<<< orphan*/  element_matching_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apply_merge_result_to_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assign_eids_to_trees (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  element_matching_info_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_trees (int /*<<< orphan*/ **,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pathrev_str (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose_notify (char*,...) ; 

__attribute__((used)) static svn_error_t *
merge_elements_one_source(svn_boolean_t *use_sleep,
                          const svn_client__pathrev_t *src_left,
                          const svn_client__pathrev_t *src_right,
                          merge_target_t *target,
                          svn_ra_session_t *ra_session,
                          element_matching_info_t *element_matching_info,
                          svn_boolean_t diff_ignore_ancestry,
                          svn_boolean_t force_delete,
                          svn_boolean_t dry_run,
                          const apr_array_header_t *merge_options,
                          svn_client_ctx_t *ctx,
                          apr_pool_t *scratch_pool)
{
  svn_element__tree_t *tree_left, *tree_right, *tree_target;
  svn_element__tree_t *merge_result;
  void *conflicts;

  verbose_notify("--- Merging by elements: "
                 "left=%s, right=%s, matching=%s",
                 pathrev_str(src_left, scratch_pool),
                 pathrev_str(src_right, scratch_pool),
                 element_matching_info_str(element_matching_info,
                                           scratch_pool));

  /* assign EIDs (in memory) to the source-left, source-right and target
     trees */
  SVN_ERR(assign_eids_to_trees(&tree_left, &tree_right, &tree_target,
                               src_left, src_right, target, ra_session,
                               element_matching_info,
                               ctx, scratch_pool, scratch_pool));

  /* perform a tree merge, creating a temporary result (in memory) */
  SVN_ERR(merge_trees(&merge_result, &conflicts,
                      tree_left, tree_right, tree_target,
                      scratch_pool, scratch_pool));

  /* check for (new style) conflicts in the result; if any, bail out */
  if (conflicts)
    {
      return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                              _("Merge had conflicts; "
                                "this is not yet supported"));
    }

  /* convert the result to a series of WC edits and apply those to the WC */
  if (dry_run)
    {
      verbose_notify("--- Dry run; not writing merge result to WC");
    }
  else
    {
      SVN_ERR(apply_merge_result_to_wc(target, merge_result,
                                       ctx, scratch_pool));
      *use_sleep = TRUE;
    }

  /* forget all the EID metadata */
  return SVN_NO_ERROR;
}