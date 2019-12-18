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
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 scalar_t__ preemptible () ; 
 int /*<<< orphan*/  x2apic_extra_bits ; 

__attribute__((used)) static unsigned int x2apic_get_apic_id(unsigned long x)
{
	unsigned int id;

	WARN_ON(preemptible() && num_online_cpus() > 1);
	id = x | __this_cpu_read(x2apic_extra_bits);

	return id;
}