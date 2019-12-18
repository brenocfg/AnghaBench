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
 int /*<<< orphan*/  PLATFORM_CPU_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  plat_obj ; 
 int /*<<< orphan*/  printf (char*) ; 

void
cpu_reset(void)
{

	PLATFORM_CPU_RESET(plat_obj);

	printf("cpu_reset failed");

	intr_disable();
	while(1) {
		cpu_sleep(0);
	}
}