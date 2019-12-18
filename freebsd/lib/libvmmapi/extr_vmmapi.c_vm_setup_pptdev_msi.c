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
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_pptdev_msi {int vcpu; int bus; int slot; int func; int numvec; void* addr; void* msg; } ;
typedef  int /*<<< orphan*/  pptmsi ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PPTDEV_MSI ; 
 int /*<<< orphan*/  bzero (struct vm_pptdev_msi*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_pptdev_msi*) ; 

int
vm_setup_pptdev_msi(struct vmctx *ctx, int vcpu, int bus, int slot, int func,
    uint64_t addr, uint64_t msg, int numvec)
{
	struct vm_pptdev_msi pptmsi;

	bzero(&pptmsi, sizeof(pptmsi));
	pptmsi.vcpu = vcpu;
	pptmsi.bus = bus;
	pptmsi.slot = slot;
	pptmsi.func = func;
	pptmsi.msg = msg;
	pptmsi.addr = addr;
	pptmsi.numvec = numvec;

	return (ioctl(ctx->fd, VM_PPTDEV_MSI, &pptmsi));
}