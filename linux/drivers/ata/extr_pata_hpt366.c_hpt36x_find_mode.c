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
typedef  int u32 ;
struct hpt_clock {int xfer_mode; int timing; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct hpt_clock* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static u32 hpt36x_find_mode(struct ata_port *ap, int speed)
{
	struct hpt_clock *clocks = ap->host->private_data;

	while (clocks->xfer_mode) {
		if (clocks->xfer_mode == speed)
			return clocks->timing;
		clocks++;
	}
	BUG();
	return 0xffffffffU;	/* silence compiler warning */
}