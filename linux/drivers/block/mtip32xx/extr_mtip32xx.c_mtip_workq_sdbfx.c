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
typedef  int u32 ;
struct mtip_port {scalar_t__* completed; struct driver_data* dd; } ;
struct mtip_cmd {int dummy; } ;
struct driver_data {scalar_t__ mmio; int /*<<< orphan*/  irq_workers_active; } ;

/* Variables and functions */
 scalar_t__ HOST_IRQ_STAT ; 
 int MTIP_TAG_INTERNAL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 struct mtip_cmd* mtip_cmd_from_tag (struct driver_data*,int) ; 
 int /*<<< orphan*/  mtip_complete_command (struct mtip_cmd*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void mtip_workq_sdbfx(struct mtip_port *port, int group,
							u32 completed)
{
	struct driver_data *dd = port->dd;
	int tag, bit;
	struct mtip_cmd *command;

	if (!completed) {
		WARN_ON_ONCE(!completed);
		return;
	}
	/* clear completed status register in the hardware.*/
	writel(completed, port->completed[group]);

	/* Process completed commands. */
	for (bit = 0; (bit < 32) && completed; bit++) {
		if (completed & 0x01) {
			tag = (group << 5) | bit;

			/* skip internal command slot. */
			if (unlikely(tag == MTIP_TAG_INTERNAL))
				continue;

			command = mtip_cmd_from_tag(dd, tag);
			mtip_complete_command(command, 0);
		}
		completed >>= 1;
	}

	/* If last, re-enable interrupts */
	if (atomic_dec_return(&dd->irq_workers_active) == 0)
		writel(0xffffffff, dd->mmio + HOST_IRQ_STAT);
}