#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int* cpuctl ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 TYPE_1__* sc520_freq_table ; 

__attribute__((used)) static int sc520_freq_target(struct cpufreq_policy *policy, unsigned int state)
{

	u8 clockspeed_reg;

	local_irq_disable();

	clockspeed_reg = *cpuctl & ~0x03;
	*cpuctl = clockspeed_reg | sc520_freq_table[state].driver_data;

	local_irq_enable();

	return 0;
}