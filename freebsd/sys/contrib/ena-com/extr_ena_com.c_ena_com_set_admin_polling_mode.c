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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int polling; } ;
struct ena_com_dev {TYPE_1__ admin_queue; scalar_t__ reg_bar; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_REGS_ADMIN_INTR_MASK ; 
 scalar_t__ ENA_REGS_INTR_MASK_OFF ; 
 int /*<<< orphan*/  ENA_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ena_com_set_admin_polling_mode(struct ena_com_dev *ena_dev, bool polling)
{
	u32 mask_value = 0;

	if (polling)
		mask_value = ENA_REGS_ADMIN_INTR_MASK;

	ENA_REG_WRITE32(ena_dev->bus, mask_value,
			ena_dev->reg_bar + ENA_REGS_INTR_MASK_OFF);
	ena_dev->admin_queue.polling = polling;
}