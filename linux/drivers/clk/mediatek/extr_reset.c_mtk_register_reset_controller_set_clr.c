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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_register_reset_controller_common (struct device_node*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_reset_ops_set_clr ; 

void mtk_register_reset_controller_set_clr(struct device_node *np,
	unsigned int num_regs, int regofs)
{
	mtk_register_reset_controller_common(np, num_regs, regofs,
		&mtk_reset_ops_set_clr);
}