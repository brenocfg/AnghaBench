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
struct hpt_clock {int xfer_speed; int timing; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct hpt_clock* hpt3x2n_clocks ; 

__attribute__((used)) static u32 hpt3x2n_find_mode(struct ata_port *ap, int speed)
{
	struct hpt_clock *clocks = hpt3x2n_clocks;

	while (clocks->xfer_speed) {
		if (clocks->xfer_speed == speed)
			return clocks->timing;
		clocks++;
	}
	BUG();
	return 0xffffffffU;	/* silence compiler warning */
}