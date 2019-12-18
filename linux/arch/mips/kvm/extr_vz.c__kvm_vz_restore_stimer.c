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
typedef  scalar_t__ u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 scalar_t__ read_c0_count () ; 
 int /*<<< orphan*/  write_c0_gtoffset (scalar_t__) ; 
 int /*<<< orphan*/  write_gc0_cause (scalar_t__) ; 

__attribute__((used)) static void _kvm_vz_restore_stimer(struct kvm_vcpu *vcpu, u32 compare,
				   u32 cause)
{
	/*
	 * Avoid spurious counter interrupts by setting Guest CP0_Count to just
	 * after Guest CP0_Compare.
	 */
	write_c0_gtoffset(compare - read_c0_count());

	back_to_back_c0_hazard();
	write_gc0_cause(cause);
}