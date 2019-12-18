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
struct cpuinfo_x86 {scalar_t__ x86_capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  boot_cpu_data ; 
 int /*<<< orphan*/  clear_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  clear_cpu_cap (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ cpu_caps_cleared ; 
 int /*<<< orphan*/  set_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static inline void clear_feature(struct cpuinfo_x86 *c, unsigned int feature)
{
	/*
	 * Note: This could use the non atomic __*_bit() variants, but the
	 * rest of the cpufeature code uses atomics as well, so keep it for
	 * consistency. Cleanup all of it separately.
	 */
	if (!c) {
		clear_cpu_cap(&boot_cpu_data, feature);
		set_bit(feature, (unsigned long *)cpu_caps_cleared);
	} else {
		clear_bit(feature, (unsigned long *)c->x86_capability);
	}
}