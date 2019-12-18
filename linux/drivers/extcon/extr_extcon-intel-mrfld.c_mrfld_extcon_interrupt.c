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
struct mrfld_extcon_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCOVE_LVL1_CHGR ; 
 int /*<<< orphan*/  BCOVE_MIRQLVL1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int mrfld_extcon_cable_detect (struct mrfld_extcon_data*) ; 
 int /*<<< orphan*/  mrfld_extcon_clear (struct mrfld_extcon_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mrfld_extcon_interrupt(int irq, void *dev_id)
{
	struct mrfld_extcon_data *data = dev_id;
	int ret;

	ret = mrfld_extcon_cable_detect(data);

	mrfld_extcon_clear(data, BCOVE_MIRQLVL1, BCOVE_LVL1_CHGR);

	return ret ? IRQ_NONE: IRQ_HANDLED;
}