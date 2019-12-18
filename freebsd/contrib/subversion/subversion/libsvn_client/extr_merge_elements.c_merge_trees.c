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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  verbose_notify (char*) ; 

__attribute__((used)) static svn_error_t *
merge_trees(svn_element__tree_t **merge_result_p,
            void **conflicts_p,
            svn_element__tree_t *tree_left,
            svn_element__tree_t *tree_right,
            svn_element__tree_t *tree_target,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  verbose_notify("--- Merging trees");

  /* ### */
  *merge_result_p = NULL;
  *conflicts_p = NULL;
  return SVN_NO_ERROR;
}