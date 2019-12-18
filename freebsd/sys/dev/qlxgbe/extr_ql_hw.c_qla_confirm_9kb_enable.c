#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ enable_9kb; int /*<<< orphan*/  mbx_intr_mask_offset; } ;
struct TYPE_8__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int BIT_2 ; 
 int /*<<< orphan*/  Q8_MBOX_INT_ENABLE ; 
 int /*<<< orphan*/  Q8_MBOX_INT_MASK_MSIX ; 
 int /*<<< orphan*/  READ_REG32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla_get_nic_partition (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supports_9kb ; 

void
qla_confirm_9kb_enable(qla_host_t *ha)
{
//	uint32_t supports_9kb = 0;

	ha->hw.mbx_intr_mask_offset = READ_REG32(ha, Q8_MBOX_INT_MASK_MSIX);

	/* Use MSI-X vector 0; Enable Firmware Mailbox Interrupt */
	WRITE_REG32(ha, Q8_MBOX_INT_ENABLE, BIT_2);
	WRITE_REG32(ha, ha->hw.mbx_intr_mask_offset, 0x0);

#if 0
	qla_get_nic_partition(ha, &supports_9kb, NULL);

	if (!supports_9kb)
#endif
	ha->hw.enable_9kb = 0;

	return;
}