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
typedef  void* uint32_t ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  scalar_t__ phandle_t ;
typedef  void* pcell_t ;
typedef  unsigned long long int32_t ;
typedef  int /*<<< orphan*/  cell_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  arr ;

/* Variables and functions */
 int /*<<< orphan*/  LPCR_HVICE ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,void**,int) ; 
 int OF_getprop (scalar_t__,char*,char*,int) ; 
 int OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OPAL_REINIT_CPUS ; 
 int PPC_FEATURE2_ARCH_3_00 ; 
 int PSL_DR ; 
 int PSL_IR ; 
 void* SLBV_L ; 
 int /*<<< orphan*/  SPR_LPCR ; 
 int /*<<< orphan*/  SPR_LPID ; 
 int /*<<< orphan*/  SPR_PIR ; 
 int cpu_features2 ; 
 int /*<<< orphan*/ * cpu_idle_hook ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  lpcr ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 void* moea64_large_page_shift ; 
 unsigned long long moea64_large_page_size ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* n_slbs ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opal_check () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  powernv_boot_pir ; 
 int /*<<< orphan*/ * powernv_cpu_idle ; 
 int /*<<< orphan*/  powernv_cpuref_init () ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
powernv_attach(platform_t plat)
{
	uint32_t nptlp, shift = 0, slb_encoding = 0;
	int32_t lp_size, lp_encoding;
	char buf[255];
	pcell_t prop;
	phandle_t cpu;
	int res, len, idx;
	register_t msr;

	/* Ping OPAL again just to make sure */
	opal_check();

#if BYTE_ORDER == LITTLE_ENDIAN
	opal_call(OPAL_REINIT_CPUS, 2 /* Little endian */);
#else
	opal_call(OPAL_REINIT_CPUS, 1 /* Big endian */);
#endif

       if (cpu_idle_hook == NULL)
                cpu_idle_hook = powernv_cpu_idle;

	powernv_boot_pir = mfspr(SPR_PIR);

	/* LPID must not be altered when PSL_DR or PSL_IR is set */
	msr = mfmsr();
	mtmsr(msr & ~(PSL_DR | PSL_IR));

	/* Direct interrupts to SRR instead of HSRR and reset LPCR otherwise */
	mtspr(SPR_LPID, 0);
	isync();

	if (cpu_features2 & PPC_FEATURE2_ARCH_3_00)
		lpcr |= LPCR_HVICE;

	mtspr(SPR_LPCR, lpcr);
	isync();

	mtmsr(msr);

	powernv_cpuref_init();

	/* Set SLB count from device tree */
	cpu = OF_peer(0);
	cpu = OF_child(cpu);
	while (cpu != 0) {
		res = OF_getprop(cpu, "name", buf, sizeof(buf));
		if (res > 0 && strcmp(buf, "cpus") == 0)
			break;
		cpu = OF_peer(cpu);
	}
	if (cpu == 0)
		goto out;

	cpu = OF_child(cpu);
	while (cpu != 0) {
		res = OF_getprop(cpu, "device_type", buf, sizeof(buf));
		if (res > 0 && strcmp(buf, "cpu") == 0)
			break;
		cpu = OF_peer(cpu);
	}
	if (cpu == 0)
		goto out;

	res = OF_getencprop(cpu, "ibm,slb-size", &prop, sizeof(prop));
	if (res > 0)
		n_slbs = prop;

	/*
	 * Scan the large page size property for PAPR compatible machines.
	 * See PAPR D.5 Changes to Section 5.1.4, 'CPU Node Properties'
	 * for the encoding of the property.
	 */

	len = OF_getproplen(cpu, "ibm,segment-page-sizes");
	if (len > 0) {
		/*
		 * We have to use a variable length array on the stack
		 * since we have very limited stack space.
		 */
		pcell_t arr[len/sizeof(cell_t)];
		res = OF_getencprop(cpu, "ibm,segment-page-sizes", arr,
		    sizeof(arr));
		len /= 4;
		idx = 0;
		while (len > 0) {
			shift = arr[idx];
			slb_encoding = arr[idx + 1];
			nptlp = arr[idx + 2];
			idx += 3;
			len -= 3;
			while (len > 0 && nptlp) {
				lp_size = arr[idx];
				lp_encoding = arr[idx+1];
				if (slb_encoding == SLBV_L && lp_encoding == 0)
					break;

				idx += 2;
				len -= 2;
				nptlp--;
			}
			if (nptlp && slb_encoding == SLBV_L && lp_encoding == 0)
				break;
		}

		if (len == 0)
			panic("Standard large pages (SLB[L] = 1, PTE[LP] = 0) "
			    "not supported by this system.");

		moea64_large_page_shift = shift;
		moea64_large_page_size = 1ULL << lp_size;
	}

out:
	return (0);
}