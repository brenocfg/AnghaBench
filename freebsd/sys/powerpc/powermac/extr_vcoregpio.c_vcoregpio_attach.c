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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_post_change ; 
 int /*<<< orphan*/  cpufreq_pre_change ; 
 int /*<<< orphan*/  vcoregpio_post_change ; 
 int /*<<< orphan*/  vcoregpio_pre_change ; 

__attribute__((used)) static int
vcoregpio_attach(device_t dev)
{
	EVENTHANDLER_REGISTER(cpufreq_pre_change, vcoregpio_pre_change, dev,
	    EVENTHANDLER_PRI_ANY);
	EVENTHANDLER_REGISTER(cpufreq_post_change, vcoregpio_post_change, dev,
	    EVENTHANDLER_PRI_ANY);

	return (0);
}