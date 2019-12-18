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
 int /*<<< orphan*/  ti_cpu_reset () ; 

__attribute__((used)) static void
ti_plat_cpu_reset(platform_t plat)
{
	if (ti_cpu_reset)
		(*ti_cpu_reset)();
	else
		printf("no cpu_reset implementation\n");
}