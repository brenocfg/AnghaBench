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
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

void machine_restart(char *cmd)
{
	do_kernel_restart(cmd);
	/* Give the restart hook 1 s to take us down */
	mdelay(1000);
	pr_emerg("Reboot failed -- System halted\n");
	while (1);
}