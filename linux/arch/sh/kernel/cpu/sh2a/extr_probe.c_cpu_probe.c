#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ways; int way_incr; int sets; int entry_shift; scalar_t__ flags; int /*<<< orphan*/  linesz; } ;
struct TYPE_4__ {TYPE_1__ dcache; TYPE_1__ icache; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FAMILY_SH2A ; 
 int /*<<< orphan*/  CPU_HAS_DSP ; 
 int /*<<< orphan*/  CPU_HAS_FPU ; 
 int /*<<< orphan*/  CPU_HAS_OP32 ; 
 int /*<<< orphan*/  CPU_MXG ; 
 int /*<<< orphan*/  CPU_SH7201 ; 
 int /*<<< orphan*/  CPU_SH7203 ; 
 int /*<<< orphan*/  CPU_SH7206 ; 
 int /*<<< orphan*/  CPU_SH7263 ; 
 int /*<<< orphan*/  CPU_SH7264 ; 
 int /*<<< orphan*/  CPU_SH7269 ; 
 int /*<<< orphan*/  L1_CACHE_BYTES ; 
 TYPE_2__ boot_cpu_data ; 

void cpu_probe(void)
{
	boot_cpu_data.family			= CPU_FAMILY_SH2A;

	/* All SH-2A CPUs have support for 16 and 32-bit opcodes.. */
	boot_cpu_data.flags			|= CPU_HAS_OP32;

#if defined(CONFIG_CPU_SUBTYPE_SH7201)
	boot_cpu_data.type			= CPU_SH7201;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7203)
	boot_cpu_data.type			= CPU_SH7203;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7263)
	boot_cpu_data.type			= CPU_SH7263;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7264)
	boot_cpu_data.type			= CPU_SH7264;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7269)
	boot_cpu_data.type			= CPU_SH7269;
	boot_cpu_data.flags			|= CPU_HAS_FPU;
#elif defined(CONFIG_CPU_SUBTYPE_SH7206)
	boot_cpu_data.type			= CPU_SH7206;
	boot_cpu_data.flags			|= CPU_HAS_DSP;
#elif defined(CONFIG_CPU_SUBTYPE_MXG)
	boot_cpu_data.type			= CPU_MXG;
	boot_cpu_data.flags			|= CPU_HAS_DSP;
#endif

	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incr		= (1 << 11);
	boot_cpu_data.dcache.sets		= 128;
	boot_cpu_data.dcache.entry_shift	= 4;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.dcache.flags		= 0;

	/*
	 * The icache is the same as the dcache as far as this setup is
	 * concerned. The only real difference in hardware is that the icache
	 * lacks the U bit that the dcache has, none of this has any bearing
	 * on the cache info.
	 */
	boot_cpu_data.icache		= boot_cpu_data.dcache;
}