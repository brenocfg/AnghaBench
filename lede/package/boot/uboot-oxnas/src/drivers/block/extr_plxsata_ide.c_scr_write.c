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
typedef  unsigned long u32 ;

/* Variables and functions */
 int MAX_SRC_WRITE_LOOPS ; 
 int SATA_LINK_CONTROL ; 
 int SATA_LINK_DATA ; 
 int SATA_LINK_WR_ADDR ; 
 unsigned long SATA_STD_ASYNC_REGS_OFF ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned long** sata_regs_base ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void scr_write(int device, unsigned int sc_reg, u32 val)
{
	/* Setup the data for the write */
	*(sata_regs_base[device] + SATA_LINK_DATA) = val;

	/* Setup adr of required register. std regs start eight into async region */
	*(sata_regs_base[device] + SATA_LINK_WR_ADDR) = sc_reg
		* 4+ SATA_STD_ASYNC_REGS_OFF;

	/* Wait for data to be written */
	int loops = MAX_SRC_WRITE_LOOPS;
	do {
		if (*(sata_regs_base[device] + SATA_LINK_CONTROL) & 1UL) {
			break;
		}
		udelay(10);
	} while (--loops);

	if (!loops) {
		printf("scr_write() Timed out of wait for write completion\n");
	}
}