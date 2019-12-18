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
struct x86_cpu_desc {int x86_family; int x86_model; scalar_t__ x86_vendor; scalar_t__ x86_stepping; } ;
struct cpuinfo_x86 {scalar_t__ x86_vendor; int x86; int x86_model; scalar_t__ x86_stepping; } ;

/* Variables and functions */
 struct cpuinfo_x86 boot_cpu_data ; 

__attribute__((used)) static const struct x86_cpu_desc *
x86_match_cpu_with_stepping(const struct x86_cpu_desc *match)
{
	struct cpuinfo_x86 *c = &boot_cpu_data;
	const struct x86_cpu_desc *m;

	for (m = match; m->x86_family | m->x86_model; m++) {
		if (c->x86_vendor != m->x86_vendor)
			continue;
		if (c->x86 != m->x86_family)
			continue;
		if (c->x86_model != m->x86_model)
			continue;
		if (c->x86_stepping != m->x86_stepping)
			continue;
		return m;
	}
	return NULL;
}