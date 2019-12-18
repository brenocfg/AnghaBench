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
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  cell_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOENT ; 
 int ENXIO ; 
#define  IBM750FX 139 
#define  IBM970 138 
#define  IBM970FX 137 
#define  IBM970MP 136 
#define  MPC7400 135 
#define  MPC7410 134 
#define  MPC7447A 133 
#define  MPC7448 132 
#define  MPC7450 131 
#define  MPC7455 130 
#define  MPC7457 129 
#define  MPC750 128 
 int /*<<< orphan*/  OF_child (int /*<<< orphan*/ ) ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC970N_CYCLES ; 
 int /*<<< orphan*/  PMCN_CYCLES ; 
 int PSL_EE ; 
 int /*<<< orphan*/  SPR_970MMCR0 ; 
 int /*<<< orphan*/  SPR_970MMCR0_PMC1SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_970MMCR1 ; 
 int /*<<< orphan*/  SPR_970MMCRA ; 
 int /*<<< orphan*/  SPR_970PMC1 ; 
 int /*<<< orphan*/  SPR_MMCR0 ; 
 int /*<<< orphan*/  SPR_MMCR0_FC ; 
 int /*<<< orphan*/  SPR_MMCR0_PMC1SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_PMC1 ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_sync () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
cpu_est_clockrate(int cpu_id, uint64_t *cps)
{
	uint16_t	vers;
	register_t	msr;
	phandle_t	cpu, dev, root;
	int		res  = 0;
	char		buf[8];

	vers = mfpvr() >> 16;
	msr = mfmsr();
	mtmsr(msr & ~PSL_EE);

	switch (vers) {
		case MPC7450:
		case MPC7455:
		case MPC7457:
		case MPC750:
		case IBM750FX:
		case MPC7400:
		case MPC7410:
		case MPC7447A:
		case MPC7448:
			mtspr(SPR_MMCR0, SPR_MMCR0_FC);
			mtspr(SPR_PMC1, 0);
			mtspr(SPR_MMCR0, SPR_MMCR0_PMC1SEL(PMCN_CYCLES));
			DELAY(1000);
			*cps = (mfspr(SPR_PMC1) * 1000) + 4999;
			mtspr(SPR_MMCR0, SPR_MMCR0_FC);

			mtmsr(msr);
			return (0);
		case IBM970:
		case IBM970FX:
		case IBM970MP:
			isync();
			mtspr(SPR_970MMCR0, SPR_MMCR0_FC);
			isync();
			mtspr(SPR_970MMCR1, 0);
			mtspr(SPR_970MMCRA, 0);
			mtspr(SPR_970PMC1, 0);
			mtspr(SPR_970MMCR0,
			    SPR_970MMCR0_PMC1SEL(PMC970N_CYCLES));
			isync();
			DELAY(1000);
			powerpc_sync();
			mtspr(SPR_970MMCR0, SPR_MMCR0_FC);
			*cps = (mfspr(SPR_970PMC1) * 1000) + 4999;

			mtmsr(msr);
			return (0);

		default:
			root = OF_peer(0);
			if (root == 0)
				return (ENXIO);

			dev = OF_child(root);
			while (dev != 0) {
				res = OF_getprop(dev, "name", buf, sizeof(buf));
				if (res > 0 && strcmp(buf, "cpus") == 0)
					break;
				dev = OF_peer(dev);
			}
			cpu = OF_child(dev);
			while (cpu != 0) {
				res = OF_getprop(cpu, "device_type", buf,
						sizeof(buf));
				if (res > 0 && strcmp(buf, "cpu") == 0)
					break;
				cpu = OF_peer(cpu);
			}
			if (cpu == 0)
				return (ENOENT);
			if (OF_getprop(cpu, "ibm,extended-clock-frequency",
			    cps, sizeof(*cps)) >= 0) {
				return (0);
			} else if (OF_getprop(cpu, "clock-frequency", cps, 
			    sizeof(cell_t)) >= 0) {
				*cps >>= 32;
				return (0);
			} else {
				return (ENOENT);
			}
	}
}