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

/* Variables and functions */
 unsigned char* gdb_cpu_getreg (int,size_t*) ; 
 int /*<<< orphan*/  gdb_tx_char (char) ; 
 int /*<<< orphan*/  gdb_tx_mem (unsigned char*,size_t) ; 

void
gdb_tx_reg(int regnum)
{
	unsigned char *regp;
	size_t regsz;

	regp = gdb_cpu_getreg(regnum, &regsz);
	if (regp == NULL) {
		/* Register unavailable. */
		while (regsz--) {
			gdb_tx_char('x');
			gdb_tx_char('x');
		}
	} else
		gdb_tx_mem(regp, regsz);
}