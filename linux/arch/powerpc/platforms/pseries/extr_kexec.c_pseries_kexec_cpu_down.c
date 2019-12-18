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
struct TYPE_2__ {scalar_t__ dtl_enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_SPLPAR ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_lppaca () ; 
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int smp_processor_id () ; 
 int unregister_dtl (int) ; 
 int unregister_slb_shadow (int) ; 
 int unregister_vpa (int) ; 
 int /*<<< orphan*/  xics_kexec_teardown_cpu (int) ; 
 scalar_t__ xive_enabled () ; 
 int /*<<< orphan*/  xive_shutdown () ; 
 int /*<<< orphan*/  xive_teardown_cpu () ; 

void pseries_kexec_cpu_down(int crash_shutdown, int secondary)
{
	/*
	 * Don't risk a hypervisor call if we're crashing
	 * XXX: Why? The hypervisor is not crashing. It might be better
	 * to at least attempt unregister to avoid the hypervisor stepping
	 * on our memory.
	 */
	if (firmware_has_feature(FW_FEATURE_SPLPAR) && !crash_shutdown) {
		int ret;
		int cpu = smp_processor_id();
		int hwcpu = hard_smp_processor_id();

		if (get_lppaca()->dtl_enable_mask) {
			ret = unregister_dtl(hwcpu);
			if (ret) {
				pr_err("WARNING: DTL deregistration for cpu "
				       "%d (hw %d) failed with %d\n",
				       cpu, hwcpu, ret);
			}
		}

		ret = unregister_slb_shadow(hwcpu);
		if (ret) {
			pr_err("WARNING: SLB shadow buffer deregistration "
			       "for cpu %d (hw %d) failed with %d\n",
			       cpu, hwcpu, ret);
		}

		ret = unregister_vpa(hwcpu);
		if (ret) {
			pr_err("WARNING: VPA deregistration for cpu %d "
			       "(hw %d) failed with %d\n", cpu, hwcpu, ret);
		}
	}

	if (xive_enabled()) {
		xive_teardown_cpu();

		if (!secondary)
			xive_shutdown();
	} else
		xics_kexec_teardown_cpu(secondary);
}