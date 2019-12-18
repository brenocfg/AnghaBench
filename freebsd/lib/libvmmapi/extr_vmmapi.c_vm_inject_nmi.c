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
typedef  int /*<<< orphan*/  vmnmi ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_nmi {int cpuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_INJECT_NMI ; 
 int /*<<< orphan*/  bzero (struct vm_nmi*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_nmi*) ; 

int
vm_inject_nmi(struct vmctx *ctx, int vcpu)
{
	struct vm_nmi vmnmi;

	bzero(&vmnmi, sizeof(vmnmi));
	vmnmi.cpuid = vcpu;

	return (ioctl(ctx->fd, VM_INJECT_NMI, &vmnmi));
}