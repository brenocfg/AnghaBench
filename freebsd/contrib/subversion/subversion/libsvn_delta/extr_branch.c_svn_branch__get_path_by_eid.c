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
typedef  int /*<<< orphan*/  svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  EID_IS_ALLOCATED (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_branch__state_get_elements (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char const* svn_element__tree_get_path_by_eid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

const char *
svn_branch__get_path_by_eid(const svn_branch__state_t *branch,
                            int eid,
                            apr_pool_t *result_pool)
{
  svn_element__tree_t *elements;

  SVN_ERR_ASSERT_NO_RETURN(EID_IS_ALLOCATED(branch, eid));
  /*SVN_ERR_ASSERT_NO_RETURN(branch->priv->is_flat);*/

  svn_error_clear(svn_branch__state_get_elements(branch, &elements, result_pool));
  return svn_element__tree_get_path_by_eid(elements, eid, result_pool);
}