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
typedef  int /*<<< orphan*/  svn_element__content_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * branch_get_element (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static svn_error_t *
branch_state_get_element(const svn_branch__state_t *branch,
                         svn_element__content_t **element_p,
                         int eid,
                         apr_pool_t *result_pool)
{
  *element_p = branch_get_element(branch, eid);
  return SVN_NO_ERROR;
}