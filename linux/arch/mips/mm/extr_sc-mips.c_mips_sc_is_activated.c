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
struct TYPE_2__ {int linesz; } ;
struct cpuinfo_mips {TYPE_1__ scache; } ;

/* Variables and functions */
#define  CPU_1004K 137 
#define  CPU_1074K 136 
#define  CPU_34K 135 
#define  CPU_74K 134 
#define  CPU_BMIPS5000 133 
#define  CPU_INTERAPTIV 132 
#define  CPU_P5600 131 
#define  CPU_P6600 130 
#define  CPU_PROAPTIV 129 
#define  CPU_QEMU_GENERIC 128 
 int current_cpu_type () ; 
 unsigned int read_c0_config2 () ; 

__attribute__((used)) static inline int mips_sc_is_activated(struct cpuinfo_mips *c)
{
	unsigned int config2 = read_c0_config2();
	unsigned int tmp;

	/* Check the bypass bit (L2B) */
	switch (current_cpu_type()) {
	case CPU_34K:
	case CPU_74K:
	case CPU_1004K:
	case CPU_1074K:
	case CPU_INTERAPTIV:
	case CPU_PROAPTIV:
	case CPU_P5600:
	case CPU_BMIPS5000:
	case CPU_QEMU_GENERIC:
	case CPU_P6600:
		if (config2 & (1 << 12))
			return 0;
	}

	tmp = (config2 >> 4) & 0x0f;
	if (0 < tmp && tmp <= 7)
		c->scache.linesz = 2 << tmp;
	else
		return 0;
	return 1;
}