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
struct cf_setting {int freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cpufreq_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4tcc_set (int /*<<< orphan*/ ,struct cf_setting*) ; 

__attribute__((used)) static int
p4tcc_detach(device_t dev)
{
	struct cf_setting set;
	int error;

	error = cpufreq_unregister(dev);
	if (error)
		return (error);

	/*
	 * Before we finish detach, switch to Automatic mode.
	 */
	set.freq = 10000;
	p4tcc_set(dev, &set);
	return(0);
}