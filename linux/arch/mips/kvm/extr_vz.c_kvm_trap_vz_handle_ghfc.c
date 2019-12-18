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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int /*<<< orphan*/  trace_kvm_guest_mode_change (struct kvm_vcpu*) ; 

__attribute__((used)) static enum emulation_result kvm_trap_vz_handle_ghfc(u32 cause, u32 *opc,
						     struct kvm_vcpu *vcpu)
{
	/*
	 * Presumably this is due to MC (guest mode change), so lets trace some
	 * relevant info.
	 */
	trace_kvm_guest_mode_change(vcpu);

	return EMULATE_DONE;
}