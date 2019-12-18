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
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 
 int /*<<< orphan*/  prom_service_exists (char const*) ; 

void prom_sun4v_guest_soft_state(void)
{
	const char *svc = "SUNW,soft-state-supported";
	unsigned long args[3];

	if (!prom_service_exists(svc))
		return;
	args[0] = (unsigned long) svc;
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
}