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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  zynq7_cpu_reset () ; 

__attribute__((used)) static void
zynq7_do_cpu_reset(platform_t plat)
{
	if (zynq7_cpu_reset != NULL)
		(*zynq7_cpu_reset)();

	printf("cpu_reset: no platform cpu_reset.  hanging.\n");
	for (;;)
		;
}