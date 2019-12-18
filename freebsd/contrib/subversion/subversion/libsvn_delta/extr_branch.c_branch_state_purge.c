#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  is_flat; TYPE_1__* element_tree; } ;
struct TYPE_5__ {int /*<<< orphan*/  root_eid; int /*<<< orphan*/  e_map; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_element__tree_purge_orphans (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
branch_state_purge(svn_branch__state_t *branch,
                   apr_pool_t *scratch_pool)
{
  svn_element__tree_purge_orphans(branch->priv->element_tree->e_map,
                                  branch->priv->element_tree->root_eid,
                                  scratch_pool);
  branch->priv->is_flat = TRUE;
  return SVN_NO_ERROR;
}