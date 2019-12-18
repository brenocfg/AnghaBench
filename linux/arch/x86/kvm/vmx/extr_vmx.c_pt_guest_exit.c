#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ctl; } ;
struct TYPE_5__ {int ctl; } ;
struct TYPE_4__ {TYPE_3__ host; int /*<<< orphan*/  addr_range; TYPE_2__ guest; } ;
struct vcpu_vmx {TYPE_1__ pt_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_RTIT_CTL ; 
 scalar_t__ PT_MODE_SYSTEM ; 
 int RTIT_CTL_TRACEEN ; 
 int /*<<< orphan*/  pt_load_msr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_mode ; 
 int /*<<< orphan*/  pt_save_msr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_guest_exit(struct vcpu_vmx *vmx)
{
	if (pt_mode == PT_MODE_SYSTEM)
		return;

	if (vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN) {
		pt_save_msr(&vmx->pt_desc.guest, vmx->pt_desc.addr_range);
		pt_load_msr(&vmx->pt_desc.host, vmx->pt_desc.addr_range);
	}

	/* Reload host state (IA32_RTIT_CTL will be cleared on VM exit). */
	wrmsrl(MSR_IA32_RTIT_CTL, vmx->pt_desc.host.ctl);
}