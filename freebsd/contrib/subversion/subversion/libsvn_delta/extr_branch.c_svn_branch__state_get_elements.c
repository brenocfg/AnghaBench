#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_element__tree_t ;
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_elements ) (TYPE_2__ const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_branch__state_get_elements(const svn_branch__state_t *branch,
                               svn_element__tree_t **element_tree_p,
                               apr_pool_t *result_pool)
{
  SVN_ERR(branch->vtable->get_elements(branch,
                                       element_tree_p,
                                       result_pool));
  return SVN_NO_ERROR;
}