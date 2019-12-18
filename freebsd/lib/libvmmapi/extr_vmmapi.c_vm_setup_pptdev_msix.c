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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_pptdev_msix {int vcpu; int bus; int slot; int func; int idx; int /*<<< orphan*/  vector_control; void* addr; void* msg; } ;
typedef  int /*<<< orphan*/  pptmsix ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PPTDEV_MSIX ; 
 int /*<<< orphan*/  bzero (struct vm_pptdev_msix*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_pptdev_msix*) ; 

int	
vm_setup_pptdev_msix(struct vmctx *ctx, int vcpu, int bus, int slot, int func,
    int idx, uint64_t addr, uint64_t msg, uint32_t vector_control)
{
	struct vm_pptdev_msix pptmsix;

	bzero(&pptmsix, sizeof(pptmsix));
	pptmsix.vcpu = vcpu;
	pptmsix.bus = bus;
	pptmsix.slot = slot;
	pptmsix.func = func;
	pptmsix.idx = idx;
	pptmsix.msg = msg;
	pptmsix.addr = addr;
	pptmsix.vector_control = vector_control;

	return ioctl(ctx->fd, VM_PPTDEV_MSIX, &pptmsix);
}