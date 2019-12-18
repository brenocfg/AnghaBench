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
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCPUOP_is_up ; 
 int /*<<< orphan*/  lapic_create (int,int) ; 
 int /*<<< orphan*/  lapic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_id ; 

__attribute__((used)) static int
xenpv_setup_local(void)
{
#ifdef SMP
	int i, ret;

	for (i = 0; i < MAXCPU && (i * 2) < MAX_APIC_ID; i++) {
		ret = HYPERVISOR_vcpu_op(VCPUOP_is_up, i, NULL);
		if (ret >= 0)
			lapic_create((i * 2), (i == 0));
	}
#endif

	PCPU_SET(vcpu_id, 0);
	lapic_init(0);
	return (0);
}