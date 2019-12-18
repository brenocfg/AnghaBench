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
struct TYPE_2__ {int linesz; int ways; int sets; int flags; int waysize; int /*<<< orphan*/  waybit; } ;
struct cpuinfo_mips {int isa_level; int /*<<< orphan*/  options; TYPE_1__ scache; } ;

/* Variables and functions */
#define  CPU_CAVIUM_OCTEON3 142 
#define  CPU_LOONGSON2 141 
#define  CPU_LOONGSON3 140 
#define  CPU_NEVADA 139 
#define  CPU_R10000 138 
#define  CPU_R12000 137 
#define  CPU_R14000 136 
#define  CPU_R16000 135 
#define  CPU_R4000MC 134 
#define  CPU_R4000SC 133 
#define  CPU_R4400MC 132 
#define  CPU_R4400SC 131 
#define  CPU_R5000 130 
#define  CPU_RM7000 129 
#define  CPU_XLP 128 
 int MIPS_CACHE_NOT_PRESENT ; 
 int /*<<< orphan*/  MIPS_CPU_CACHE_CDEX_S ; 
 int /*<<< orphan*/  MIPS_CPU_INCLUSIVE_CACHES ; 
 int MIPS_CPU_ISA_M32R1 ; 
 int MIPS_CPU_ISA_M32R2 ; 
 int MIPS_CPU_ISA_M32R6 ; 
 int MIPS_CPU_ISA_M64R1 ; 
 int MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_ISA_M64R6 ; 
 unsigned int R10K_CONF_SS ; 
 struct cpuinfo_mips current_cpu_data ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  loongson2_sc_init () ; 
 int /*<<< orphan*/  loongson3_sc_init () ; 
 int /*<<< orphan*/  mips_sc_init () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  probe_scache ; 
 int /*<<< orphan*/  r5k_sc_init () ; 
 unsigned int read_c0_config () ; 
 int /*<<< orphan*/  rm7k_sc_init () ; 
 int run_uncached (int /*<<< orphan*/ ) ; 
 int scache_size ; 
 int /*<<< orphan*/ * way_string ; 

__attribute__((used)) static void setup_scache(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned int config = read_c0_config();
	int sc_present = 0;

	/*
	 * Do the probing thing on R4000SC and R4400SC processors.  Other
	 * processors don't have a S-cache that would be relevant to the
	 * Linux memory management.
	 */
	switch (current_cpu_type()) {
	case CPU_R4000SC:
	case CPU_R4000MC:
	case CPU_R4400SC:
	case CPU_R4400MC:
		sc_present = run_uncached(probe_scache);
		if (sc_present)
			c->options |= MIPS_CPU_CACHE_CDEX_S;
		break;

	case CPU_R10000:
	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		scache_size = 0x80000 << ((config & R10K_CONF_SS) >> 16);
		c->scache.linesz = 64 << ((config >> 13) & 1);
		c->scache.ways = 2;
		c->scache.waybit= 0;
		sc_present = 1;
		break;

	case CPU_R5000:
	case CPU_NEVADA:
#ifdef CONFIG_R5000_CPU_SCACHE
		r5k_sc_init();
#endif
		return;

	case CPU_RM7000:
#ifdef CONFIG_RM7000_CPU_SCACHE
		rm7k_sc_init();
#endif
		return;

	case CPU_LOONGSON2:
		loongson2_sc_init();
		return;

	case CPU_LOONGSON3:
		loongson3_sc_init();
		return;

	case CPU_CAVIUM_OCTEON3:
	case CPU_XLP:
		/* don't need to worry about L2, fully coherent */
		return;

	default:
		if (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M32R2 |
				    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R1 |
				    MIPS_CPU_ISA_M64R2 | MIPS_CPU_ISA_M64R6)) {
#ifdef CONFIG_MIPS_CPU_SCACHE
			if (mips_sc_init ()) {
				scache_size = c->scache.ways * c->scache.sets * c->scache.linesz;
				printk("MIPS secondary cache %ldkB, %s, linesize %d bytes.\n",
				       scache_size >> 10,
				       way_string[c->scache.ways], c->scache.linesz);
			}
#else
			if (!(c->scache.flags & MIPS_CACHE_NOT_PRESENT))
				panic("Dunno how to handle MIPS32 / MIPS64 second level cache");
#endif
			return;
		}
		sc_present = 0;
	}

	if (!sc_present)
		return;

	/* compute a couple of other cache variables */
	c->scache.waysize = scache_size / c->scache.ways;

	c->scache.sets = scache_size / (c->scache.linesz * c->scache.ways);

	printk("Unified secondary cache %ldkB %s, linesize %d bytes.\n",
	       scache_size >> 10, way_string[c->scache.ways], c->scache.linesz);

	c->options |= MIPS_CPU_INCLUSIVE_CACHES;
}