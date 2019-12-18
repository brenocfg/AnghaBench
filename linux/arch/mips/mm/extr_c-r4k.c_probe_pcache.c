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
struct TYPE_4__ {int linesz; int ways; int sets; int flags; int waysize; void* waybit; } ;
struct TYPE_3__ {int linesz; int ways; int sets; int flags; int waysize; void* waybit; } ;
struct cpuinfo_mips {int options; int processor_id; TYPE_2__ dcache; TYPE_1__ icache; } ;

/* Variables and functions */
 unsigned int CONF_DB ; 
 unsigned int CONF_DC ; 
 unsigned int CONF_IB ; 
 unsigned int CONF_IC ; 
 unsigned int CONF_SC ; 
#define  CPU_1004K 178 
#define  CPU_1074K 177 
#define  CPU_20KC 176 
#define  CPU_24K 175 
#define  CPU_25KF 174 
#define  CPU_34K 173 
#define  CPU_74K 172 
#define  CPU_ALCHEMY 171 
#define  CPU_BMIPS5000 170 
#define  CPU_CAVIUM_OCTEON3 169 
#define  CPU_I6400 168 
#define  CPU_I6500 167 
#define  CPU_INTERAPTIV 166 
#define  CPU_LOONGSON2 165 
#define  CPU_LOONGSON3 164 
#define  CPU_M14KC 163 
#define  CPU_M14KEC 162 
#define  CPU_M5150 161 
#define  CPU_M6250 160 
#define  CPU_NEVADA 159 
#define  CPU_P5600 158 
#define  CPU_P6600 157 
#define  CPU_PROAPTIV 156 
#define  CPU_QEMU_GENERIC 155 
#define  CPU_R10000 154 
#define  CPU_R12000 153 
#define  CPU_R14000 152 
#define  CPU_R16000 151 
#define  CPU_R4000MC 150 
#define  CPU_R4000PC 149 
#define  CPU_R4000SC 148 
#define  CPU_R4400MC 147 
#define  CPU_R4400PC 146 
#define  CPU_R4400SC 145 
#define  CPU_R4600 144 
#define  CPU_R4700 143 
#define  CPU_R5000 142 
#define  CPU_R5500 141 
#define  CPU_RM7000 140 
#define  CPU_SB1 139 
#define  CPU_SB1A 138 
#define  CPU_TX49XX 137 
#define  CPU_VR4111 136 
#define  CPU_VR4121 135 
#define  CPU_VR4122 134 
#define  CPU_VR4131 133 
#define  CPU_VR4133 132 
#define  CPU_VR4181 131 
#define  CPU_VR4181A 130 
#define  CPU_VR41XX 129 
#define  CPU_XLR 128 
 int MIPS_CACHE_ALIASES ; 
 int MIPS_CACHE_IC_F_DC ; 
 int MIPS_CACHE_PINDEX ; 
 int MIPS_CACHE_VTAG ; 
 int MIPS_CONF7_AR ; 
 int MIPS_CONF7_IAR ; 
 unsigned int MIPS_CONF_M ; 
 unsigned int MIPS_CONF_VI ; 
 int MIPS_CPU_CACHE_CDEX_P ; 
 int MIPS_CPU_PREFETCH ; 
 int MIPS_IC_SNOOPS_REMOTE ; 
 int PAGE_SIZE ; 
 unsigned int PRID_IMP_MASK ; 
 unsigned int PRID_IMP_R4000 ; 
 unsigned int PRID_REV_LOONGSON3A_R2_0 ; 
 unsigned int PRID_REV_MASK ; 
 unsigned int PRID_REV_R4400 ; 
 unsigned int R10K_CONF_DC ; 
 unsigned int R10K_CONF_IC ; 
 unsigned int VR41_CONF_BP ; 
 unsigned int VR41_CONF_P4K ; 
 void* __ffs (int) ; 
 int alias_74k_erratum (struct cpuinfo_mips*) ; 
 struct cpuinfo_mips current_cpu_data ; 
 int current_cpu_type () ; 
 int dcache_size ; 
 int icache_size ; 
 scalar_t__ mips_cm_present () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,int,char*,char*,...) ; 
 unsigned int read_c0_config () ; 
 unsigned long read_c0_config1 () ; 
 int read_c0_config7 () ; 
 unsigned int read_c0_prid () ; 
 int /*<<< orphan*/  rm7k_erratum31 () ; 
 int /*<<< orphan*/ * way_string ; 
 int /*<<< orphan*/  write_c0_config (unsigned int) ; 

__attribute__((used)) static void probe_pcache(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned int config = read_c0_config();
	unsigned int prid = read_c0_prid();
	int has_74k_erratum = 0;
	unsigned long config1;
	unsigned int lsize;

	switch (current_cpu_type()) {
	case CPU_R4600:			/* QED style two way caches? */
	case CPU_R4700:
	case CPU_R5000:
	case CPU_NEVADA:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit = __ffs(icache_size/2);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit= __ffs(dcache_size/2);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		break;

	case CPU_R5500:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P | MIPS_CPU_PREFETCH;
		break;

	case CPU_TX49XX:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PREFETCH;
		break;

	case CPU_R4000PC:
	case CPU_R4000SC:
	case CPU_R4000MC:
	case CPU_R4400PC:
	case CPU_R4400SC:
	case CPU_R4400MC:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 1;
		c->icache.waybit = 0;	/* doesn't matter */

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 1;
		c->dcache.waybit = 0;	/* does not matter */

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		break;

	case CPU_R10000:
	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		icache_size = 1 << (12 + ((config & R10K_CONF_IC) >> 29));
		c->icache.linesz = 64;
		c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & R10K_CONF_DC) >> 26));
		c->dcache.linesz = 32;
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_PREFETCH;
		break;

	case CPU_VR4133:
		write_c0_config(config & ~VR41_CONF_P4K);
		/* fall through */
	case CPU_VR4131:
		/* Workaround for cache instruction bug of VR4131 */
		if (c->processor_id == 0x0c80U || c->processor_id == 0x0c81U ||
		    c->processor_id == 0x0c82U) {
			config |= 0x00400000U;
			if (c->processor_id == 0x0c80U)
				config |= VR41_CONF_BP;
			write_c0_config(config);
		} else
			c->options |= MIPS_CPU_CACHE_CDEX_P;

		icache_size = 1 << (10 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit = __ffs(icache_size/2);

		dcache_size = 1 << (10 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit = __ffs(dcache_size/2);
		break;

	case CPU_VR41XX:
	case CPU_VR4111:
	case CPU_VR4121:
	case CPU_VR4122:
	case CPU_VR4181:
	case CPU_VR4181A:
		icache_size = 1 << (10 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 1;
		c->icache.waybit = 0;	/* doesn't matter */

		dcache_size = 1 << (10 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 1;
		c->dcache.waybit = 0;	/* does not matter */

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		break;

	case CPU_RM7000:
		rm7k_erratum31();

		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit = __ffs(icache_size / c->icache.ways);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = __ffs(dcache_size / c->dcache.ways);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PREFETCH;
		break;

	case CPU_LOONGSON2:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		if (prid & 0x3)
			c->icache.ways = 4;
		else
			c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		if (prid & 0x3)
			c->dcache.ways = 4;
		else
			c->dcache.ways = 2;
		c->dcache.waybit = 0;
		break;

	case CPU_LOONGSON3:
		config1 = read_c0_config1();
		lsize = (config1 >> 19) & 7;
		if (lsize)
			c->icache.linesz = 2 << lsize;
		else
			c->icache.linesz = 0;
		c->icache.sets = 64 << ((config1 >> 22) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);
		icache_size = c->icache.sets *
					  c->icache.ways *
					  c->icache.linesz;
		c->icache.waybit = 0;

		lsize = (config1 >> 10) & 7;
		if (lsize)
			c->dcache.linesz = 2 << lsize;
		else
			c->dcache.linesz = 0;
		c->dcache.sets = 64 << ((config1 >> 13) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);
		dcache_size = c->dcache.sets *
					  c->dcache.ways *
					  c->dcache.linesz;
		c->dcache.waybit = 0;
		if ((prid & PRID_REV_MASK) >= PRID_REV_LOONGSON3A_R2_0)
			c->options |= MIPS_CPU_PREFETCH;
		break;

	case CPU_CAVIUM_OCTEON3:
		/* For now lie about the number of ways. */
		c->icache.linesz = 128;
		c->icache.sets = 16;
		c->icache.ways = 8;
		c->icache.flags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.linesz;

		c->dcache.linesz = 128;
		c->dcache.ways = 8;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.linesz;
		c->options |= MIPS_CPU_PREFETCH;
		break;

	default:
		if (!(config & MIPS_CONF_M))
			panic("Don't know how to probe P-caches on this cpu.");

		/*
		 * So we seem to be a MIPS32 or MIPS64 CPU
		 * So let's probe the I-cache ...
		 */
		config1 = read_c0_config1();

		lsize = (config1 >> 19) & 7;

		/* IL == 7 is reserved */
		if (lsize == 7)
			panic("Invalid icache line size");

		c->icache.linesz = lsize ? 2 << lsize : 0;

		c->icache.sets = 32 << (((config1 >> 22) + 1) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);

		icache_size = c->icache.sets *
			      c->icache.ways *
			      c->icache.linesz;
		c->icache.waybit = __ffs(icache_size/c->icache.ways);

		if (config & MIPS_CONF_VI)
			c->icache.flags |= MIPS_CACHE_VTAG;

		/*
		 * Now probe the MIPS32 / MIPS64 data cache.
		 */
		c->dcache.flags = 0;

		lsize = (config1 >> 10) & 7;

		/* DL == 7 is reserved */
		if (lsize == 7)
			panic("Invalid dcache line size");

		c->dcache.linesz = lsize ? 2 << lsize : 0;

		c->dcache.sets = 32 << (((config1 >> 13) + 1) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);

		dcache_size = c->dcache.sets *
			      c->dcache.ways *
			      c->dcache.linesz;
		c->dcache.waybit = __ffs(dcache_size/c->dcache.ways);

		c->options |= MIPS_CPU_PREFETCH;
		break;
	}

	/*
	 * Processor configuration sanity check for the R4000SC erratum
	 * #5.	With page sizes larger than 32kB there is no possibility
	 * to get a VCE exception anymore so we don't care about this
	 * misconfiguration.  The case is rather theoretical anyway;
	 * presumably no vendor is shipping his hardware in the "bad"
	 * configuration.
	 */
	if ((prid & PRID_IMP_MASK) == PRID_IMP_R4000 &&
	    (prid & PRID_REV_MASK) < PRID_REV_R4400 &&
	    !(config & CONF_SC) && c->icache.linesz != 16 &&
	    PAGE_SIZE <= 0x8000)
		panic("Improper R4000SC processor configuration detected");

	/* compute a couple of other cache variables */
	c->icache.waysize = icache_size / c->icache.ways;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->icache.sets = c->icache.linesz ?
		icache_size / (c->icache.linesz * c->icache.ways) : 0;
	c->dcache.sets = c->dcache.linesz ?
		dcache_size / (c->dcache.linesz * c->dcache.ways) : 0;

	/*
	 * R1x000 P-caches are odd in a positive way.  They're 32kB 2-way
	 * virtually indexed so normally would suffer from aliases.  So
	 * normally they'd suffer from aliases but magic in the hardware deals
	 * with that for us so we don't need to take care ourselves.
	 */
	switch (current_cpu_type()) {
	case CPU_20KC:
	case CPU_25KF:
	case CPU_I6400:
	case CPU_I6500:
	case CPU_SB1:
	case CPU_SB1A:
	case CPU_XLR:
		c->dcache.flags |= MIPS_CACHE_PINDEX;
		break;

	case CPU_R10000:
	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		break;

	case CPU_74K:
	case CPU_1074K:
		has_74k_erratum = alias_74k_erratum(c);
		/* Fall through. */
	case CPU_M14KC:
	case CPU_M14KEC:
	case CPU_24K:
	case CPU_34K:
	case CPU_1004K:
	case CPU_INTERAPTIV:
	case CPU_P5600:
	case CPU_PROAPTIV:
	case CPU_M5150:
	case CPU_QEMU_GENERIC:
	case CPU_P6600:
	case CPU_M6250:
		if (!(read_c0_config7() & MIPS_CONF7_IAR) &&
		    (c->icache.waysize > PAGE_SIZE))
			c->icache.flags |= MIPS_CACHE_ALIASES;
		if (!has_74k_erratum && (read_c0_config7() & MIPS_CONF7_AR)) {
			/*
			 * Effectively physically indexed dcache,
			 * thus no virtual aliases.
			*/
			c->dcache.flags |= MIPS_CACHE_PINDEX;
			break;
		}
		/* fall through */
	default:
		if (has_74k_erratum || c->dcache.waysize > PAGE_SIZE)
			c->dcache.flags |= MIPS_CACHE_ALIASES;
	}

	/* Physically indexed caches don't suffer from virtual aliasing */
	if (c->dcache.flags & MIPS_CACHE_PINDEX)
		c->dcache.flags &= ~MIPS_CACHE_ALIASES;

	/*
	 * In systems with CM the icache fills from L2 or closer caches, and
	 * thus sees remote stores without needing to write them back any
	 * further than that.
	 */
	if (mips_cm_present())
		c->icache.flags |= MIPS_IC_SNOOPS_REMOTE;

	switch (current_cpu_type()) {
	case CPU_20KC:
		/*
		 * Some older 20Kc chips doesn't have the 'VI' bit in
		 * the config register.
		 */
		c->icache.flags |= MIPS_CACHE_VTAG;
		break;

	case CPU_ALCHEMY:
	case CPU_I6400:
	case CPU_I6500:
		c->icache.flags |= MIPS_CACHE_IC_F_DC;
		break;

	case CPU_BMIPS5000:
		c->icache.flags |= MIPS_CACHE_IC_F_DC;
		/* Cache aliases are handled in hardware; allow HIGHMEM */
		c->dcache.flags &= ~MIPS_CACHE_ALIASES;
		break;

	case CPU_LOONGSON2:
		/*
		 * LOONGSON2 has 4 way icache, but when using indexed cache op,
		 * one op will act on all 4 ways
		 */
		c->icache.ways = 1;
	}

	printk("Primary instruction cache %ldkB, %s, %s, linesize %d bytes.\n",
	       icache_size >> 10,
	       c->icache.flags & MIPS_CACHE_VTAG ? "VIVT" : "VIPT",
	       way_string[c->icache.ways], c->icache.linesz);

	printk("Primary data cache %ldkB, %s, %s, %s, linesize %d bytes\n",
	       dcache_size >> 10, way_string[c->dcache.ways],
	       (c->dcache.flags & MIPS_CACHE_PINDEX) ? "PIPT" : "VIPT",
	       (c->dcache.flags & MIPS_CACHE_ALIASES) ?
			"cache aliases" : "no aliases",
	       c->dcache.linesz);
}