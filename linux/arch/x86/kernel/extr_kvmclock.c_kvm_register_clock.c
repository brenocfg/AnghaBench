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
typedef  int u64 ;
struct pvclock_vsyscall_time_info {int /*<<< orphan*/  pvti; } ;

/* Variables and functions */
 int /*<<< orphan*/  msr_kvm_system_time ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,char*) ; 
 int slow_virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct pvclock_vsyscall_time_info* this_cpu_hvclock () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_register_clock(char *txt)
{
	struct pvclock_vsyscall_time_info *src = this_cpu_hvclock();
	u64 pa;

	if (!src)
		return;

	pa = slow_virt_to_phys(&src->pvti) | 0x01ULL;
	wrmsrl(msr_kvm_system_time, pa);
	pr_info("kvm-clock: cpu %d, msr %llx, %s", smp_processor_id(), pa, txt);
}