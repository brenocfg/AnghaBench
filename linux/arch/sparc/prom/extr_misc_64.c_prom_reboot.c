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
 scalar_t__ ldom_domaining_enabled ; 
 int /*<<< orphan*/  ldom_reboot (char const*) ; 
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 

void prom_reboot(const char *bcommand)
{
	unsigned long args[4];

#ifdef CONFIG_SUN_LDOMS
	if (ldom_domaining_enabled)
		ldom_reboot(bcommand);
#endif
	args[0] = (unsigned long) "boot";
	args[1] = 1;
	args[2] = 0;
	args[3] = (unsigned long) bcommand;

	p1275_cmd_direct(args);
}