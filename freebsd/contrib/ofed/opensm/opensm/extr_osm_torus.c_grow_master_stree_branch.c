#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct t_switch {TYPE_1__* ptgrp; } ;
struct TYPE_2__ {struct TYPE_2__* to_stree_root; struct TYPE_2__* to_stree_tip; } ;

/* Variables and functions */

__attribute__((used)) static
void grow_master_stree_branch(struct t_switch *root, struct t_switch *tip,
			      unsigned to_root_pg, unsigned to_tip_pg)
{
	root->ptgrp[to_tip_pg].to_stree_tip = &tip->ptgrp[to_root_pg];
	tip->ptgrp[to_root_pg].to_stree_root = &root->ptgrp[to_tip_pg];
}