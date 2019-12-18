#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_6__ {int x86; } ;
struct TYPE_5__ {unsigned int extcpu; int bank; int status; int mcgstatus; int inject_flags; scalar_t__ synd; scalar_t__ misc; int /*<<< orphan*/  tsc; } ;

/* Variables and functions */
#define  DFR_INT_INJ 129 
 int MCG_STATUS_EIPV ; 
 int MCG_STATUS_MCIP ; 
 int MCG_STATUS_RIPV ; 
 int MCI_STATUS_DEFERRED ; 
 int MCI_STATUS_MISCV ; 
 int MCI_STATUS_PCC ; 
 int MCI_STATUS_SYNDV ; 
 int MCI_STATUS_UC ; 
 int SW_INJ ; 
#define  THR_INT_INJ 128 
 int /*<<< orphan*/  X86_FEATURE_AMD_DCM ; 
 int /*<<< orphan*/  amd_get_nb_id (unsigned int) ; 
 TYPE_4__ boot_cpu_data ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 unsigned int get_nbc_for_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 TYPE_1__ i_mce ; 
 int inj_type ; 
 int /*<<< orphan*/  mce_inject_log (TYPE_1__*) ; 
 int /*<<< orphan*/  prepare_msrs ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rdtsc_ordered () ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggle_hw_mce_inject (unsigned int,int) ; 
 int /*<<< orphan*/  toggle_nb_mca_mst_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_dfr_int ; 
 int /*<<< orphan*/  trigger_mce ; 
 int /*<<< orphan*/  trigger_thr_int ; 

__attribute__((used)) static void do_inject(void)
{
	u64 mcg_status = 0;
	unsigned int cpu = i_mce.extcpu;
	u8 b = i_mce.bank;

	i_mce.tsc = rdtsc_ordered();

	if (i_mce.misc)
		i_mce.status |= MCI_STATUS_MISCV;

	if (i_mce.synd)
		i_mce.status |= MCI_STATUS_SYNDV;

	if (inj_type == SW_INJ) {
		mce_inject_log(&i_mce);
		return;
	}

	/* prep MCE global settings for the injection */
	mcg_status = MCG_STATUS_MCIP | MCG_STATUS_EIPV;

	if (!(i_mce.status & MCI_STATUS_PCC))
		mcg_status |= MCG_STATUS_RIPV;

	/*
	 * Ensure necessary status bits for deferred errors:
	 * - MCx_STATUS[Deferred]: make sure it is a deferred error
	 * - MCx_STATUS[UC] cleared: deferred errors are _not_ UC
	 */
	if (inj_type == DFR_INT_INJ) {
		i_mce.status |= MCI_STATUS_DEFERRED;
		i_mce.status |= (i_mce.status & ~MCI_STATUS_UC);
	}

	/*
	 * For multi node CPUs, logging and reporting of bank 4 errors happens
	 * only on the node base core. Refer to D18F3x44[NbMcaToMstCpuEn] for
	 * Fam10h and later BKDGs.
	 */
	if (boot_cpu_has(X86_FEATURE_AMD_DCM) &&
	    b == 4 &&
	    boot_cpu_data.x86 < 0x17) {
		toggle_nb_mca_mst_cpu(amd_get_nb_id(cpu));
		cpu = get_nbc_for_node(amd_get_nb_id(cpu));
	}

	get_online_cpus();
	if (!cpu_online(cpu))
		goto err;

	toggle_hw_mce_inject(cpu, true);

	i_mce.mcgstatus = mcg_status;
	i_mce.inject_flags = inj_type;
	smp_call_function_single(cpu, prepare_msrs, &i_mce, 0);

	toggle_hw_mce_inject(cpu, false);

	switch (inj_type) {
	case DFR_INT_INJ:
		smp_call_function_single(cpu, trigger_dfr_int, NULL, 0);
		break;
	case THR_INT_INJ:
		smp_call_function_single(cpu, trigger_thr_int, NULL, 0);
		break;
	default:
		smp_call_function_single(cpu, trigger_mce, NULL, 0);
	}

err:
	put_online_cpus();

}