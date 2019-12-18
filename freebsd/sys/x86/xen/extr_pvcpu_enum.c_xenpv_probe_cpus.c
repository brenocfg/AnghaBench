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

/* Variables and functions */
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int MAXCPU ; 
 int MAX_APIC_ID ; 
 int /*<<< orphan*/  VCPUOP_is_up ; 
 int max_apic_id ; 
 int min (int,int) ; 
 int mp_maxid ; 
 int mp_ncpus ; 

__attribute__((used)) static int
xenpv_probe_cpus(void)
{
#ifdef SMP
	int i, ret;

	for (i = 0; i < MAXCPU && (i * 2) < MAX_APIC_ID; i++) {
		ret = HYPERVISOR_vcpu_op(VCPUOP_is_up, i, NULL);
		mp_ncpus = min(mp_ncpus + 1, MAXCPU);
	}
	mp_maxid = mp_ncpus - 1;
	max_apic_id = mp_ncpus * 2;
#endif
	return (0);
}