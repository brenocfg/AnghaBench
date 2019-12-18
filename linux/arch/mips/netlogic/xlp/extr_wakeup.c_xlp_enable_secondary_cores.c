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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nlm_soc_info {unsigned int coremask; int /*<<< orphan*/  sysbase; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_9XX_DEVCFG6 ; 
 int NLM_NR_NODES ; 
 int NLM_THREADS_PER_CORE ; 
 int PRID_IMP_MASK ; 
#define  PRID_IMP_NETLOGIC_XLP2XX 132 
#define  PRID_IMP_NETLOGIC_XLP3XX 131 
#define  PRID_IMP_NETLOGIC_XLP5XX 130 
#define  PRID_IMP_NETLOGIC_XLP8XX 129 
#define  PRID_IMP_NETLOGIC_XLP9XX 128 
 int /*<<< orphan*/  SYS_EFUSE_DEVICE_CFG_STATUS0 ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/  const*) ; 
 int hweight32 (int) ; 
 int nlm_cores_per_node () ; 
 int /*<<< orphan*/  nlm_get_fuse_regbase (int) ; 
 struct nlm_soc_info* nlm_get_node (int) ; 
 int /*<<< orphan*/  nlm_get_sys_pcibase (int) ; 
 int /*<<< orphan*/  nlm_node_init (int) ; 
 int nlm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlm_read_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int read_c0_prid () ; 
 int /*<<< orphan*/  wait_for_cpus (int,int /*<<< orphan*/ ) ; 
 int xlp9xx_get_socbus (int) ; 
 int /*<<< orphan*/  xlp_wakeup_core (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xlp_enable_secondary_cores(const cpumask_t *wakeup_mask)
{
	struct nlm_soc_info *nodep;
	uint64_t syspcibase, fusebase;
	uint32_t syscoremask, mask, fusemask;
	int core, n, cpu, ncores;

	for (n = 0; n < NLM_NR_NODES; n++) {
		if (n != 0) {
			/* check if node exists and is online */
			if (cpu_is_xlp9xx()) {
				int b = xlp9xx_get_socbus(n);
				pr_info("Node %d SoC PCI bus %d.\n", n, b);
				if (b == 0)
					break;
			} else {
				syspcibase = nlm_get_sys_pcibase(n);
				if (nlm_read_reg(syspcibase, 0) == 0xffffffff)
					break;
			}
			nlm_node_init(n);
		}

		/* read cores in reset from SYS */
		nodep = nlm_get_node(n);

		if (cpu_is_xlp9xx()) {
			fusebase = nlm_get_fuse_regbase(n);
			fusemask = nlm_read_reg(fusebase, FUSE_9XX_DEVCFG6);
			switch (read_c0_prid() & PRID_IMP_MASK) {
			case PRID_IMP_NETLOGIC_XLP5XX:
				mask = 0xff;
				break;
			case PRID_IMP_NETLOGIC_XLP9XX:
			default:
				mask = 0xfffff;
				break;
			}
		} else {
			fusemask = nlm_read_sys_reg(nodep->sysbase,
						SYS_EFUSE_DEVICE_CFG_STATUS0);
			switch (read_c0_prid() & PRID_IMP_MASK) {
			case PRID_IMP_NETLOGIC_XLP3XX:
				mask = 0xf;
				break;
			case PRID_IMP_NETLOGIC_XLP2XX:
				mask = 0x3;
				break;
			case PRID_IMP_NETLOGIC_XLP8XX:
			default:
				mask = 0xff;
				break;
			}
		}

		/*
		 * Fused out cores are set in the fusemask, and the remaining
		 * cores are renumbered to range 0 .. nactive-1
		 */
		syscoremask = (1 << hweight32(~fusemask & mask)) - 1;

		pr_info("Node %d - SYS/FUSE coremask %x\n", n, syscoremask);
		ncores = nlm_cores_per_node();
		for (core = 0; core < ncores; core++) {
			/* we will be on node 0 core 0 */
			if (n == 0 && core == 0)
				continue;

			/* see if the core exists */
			if ((syscoremask & (1 << core)) == 0)
				continue;

			/* see if at least the first hw thread is enabled */
			cpu = (n * ncores + core) * NLM_THREADS_PER_CORE;
			if (!cpumask_test_cpu(cpu, wakeup_mask))
				continue;

			/* wake up the core */
			if (!xlp_wakeup_core(nodep->sysbase, n, core))
				continue;

			/* core is up */
			nodep->coremask |= 1u << core;

			/* spin until the hw threads sets their ready */
			if (!wait_for_cpus(cpu, 0))
				pr_err("Node %d : timeout core %d\n", n, core);
		}
	}
}