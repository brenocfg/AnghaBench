#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int /*<<< orphan*/  pm_slb_tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_slb_tree_node (int /*<<< orphan*/ ) ; 

void
slb_free_tree(pmap_t pm)
{

	free_slb_tree_node(pm->pm_slb_tree_root);
}