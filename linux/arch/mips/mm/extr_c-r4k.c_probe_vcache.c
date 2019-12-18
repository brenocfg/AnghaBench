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
struct TYPE_2__ {int linesz; int sets; int ways; int waysize; scalar_t__ waybit; } ;
struct cpuinfo_mips {TYPE_1__ vcache; } ;

/* Variables and functions */
 scalar_t__ CPU_LOONGSON3 ; 
 struct cpuinfo_mips current_cpu_data ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int) ; 
 unsigned int read_c0_config2 () ; 
 int vcache_size ; 
 int /*<<< orphan*/ * way_string ; 

__attribute__((used)) static void probe_vcache(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned int config2, lsize;

	if (current_cpu_type() != CPU_LOONGSON3)
		return;

	config2 = read_c0_config2();
	if ((lsize = ((config2 >> 20) & 15)))
		c->vcache.linesz = 2 << lsize;
	else
		c->vcache.linesz = lsize;

	c->vcache.sets = 64 << ((config2 >> 24) & 15);
	c->vcache.ways = 1 + ((config2 >> 16) & 15);

	vcache_size = c->vcache.sets * c->vcache.ways * c->vcache.linesz;

	c->vcache.waybit = 0;
	c->vcache.waysize = vcache_size / c->vcache.ways;

	pr_info("Unified victim cache %ldkB %s, linesize %d bytes.\n",
		vcache_size >> 10, way_string[c->vcache.ways], c->vcache.linesz);
}