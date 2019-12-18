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
typedef  int /*<<< orphan*/  u_long ;
struct cpuref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_TIMEBASE_FREQ (int /*<<< orphan*/ ,struct cpuref*) ; 
 int /*<<< orphan*/  plat_obj ; 

u_long
platform_timebase_freq(struct cpuref *cpu)
{
	return (PLATFORM_TIMEBASE_FREQ(plat_obj, cpu));
}