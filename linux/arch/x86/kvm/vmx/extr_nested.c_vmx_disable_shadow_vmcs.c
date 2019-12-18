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
struct TYPE_2__ {int need_vmcs12_to_shadow_sync; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECONDARY_EXEC_SHADOW_VMCS ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int /*<<< orphan*/  secondary_exec_controls_clearbit (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void vmx_disable_shadow_vmcs(struct vcpu_vmx *vmx)
{
	secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_SHADOW_VMCS);
	vmcs_write64(VMCS_LINK_POINTER, -1ull);
	vmx->nested.need_vmcs12_to_shadow_sync = false;
}