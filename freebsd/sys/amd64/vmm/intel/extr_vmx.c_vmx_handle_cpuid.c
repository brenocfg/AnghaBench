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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmxctx {int guest_rax; int /*<<< orphan*/  guest_rdx; int /*<<< orphan*/  guest_rcx; int /*<<< orphan*/  guest_rbx; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int x86_emulate_cpuid (struct vm*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vmx_handle_cpuid(struct vm *vm, int vcpu, struct vmxctx *vmxctx)
{
	int handled, func;

	func = vmxctx->guest_rax;

	handled = x86_emulate_cpuid(vm, vcpu,
				    (uint32_t*)(&vmxctx->guest_rax),
				    (uint32_t*)(&vmxctx->guest_rbx),
				    (uint32_t*)(&vmxctx->guest_rcx),
				    (uint32_t*)(&vmxctx->guest_rdx));
	return (handled);
}