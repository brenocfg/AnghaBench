#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vcpu_vmx {TYPE_2__* loaded_vmcs; } ;
struct TYPE_3__ {unsigned long rsp; } ;
struct TYPE_4__ {TYPE_1__ host_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_RSP ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 

void vmx_update_host_rsp(struct vcpu_vmx *vmx, unsigned long host_rsp)
{
	if (unlikely(host_rsp != vmx->loaded_vmcs->host_state.rsp)) {
		vmx->loaded_vmcs->host_state.rsp = host_rsp;
		vmcs_writel(HOST_RSP, host_rsp);
	}
}