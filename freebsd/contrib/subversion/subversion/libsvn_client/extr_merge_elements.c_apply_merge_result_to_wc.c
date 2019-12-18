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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  verbose_notify (char*) ; 

__attribute__((used)) static svn_error_t *
apply_merge_result_to_wc(merge_target_t *target,
                         svn_element__tree_t *merge_result,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *scratch_pool)
{
  verbose_notify("--- Writing merge result to WC");

  return SVN_NO_ERROR;
}