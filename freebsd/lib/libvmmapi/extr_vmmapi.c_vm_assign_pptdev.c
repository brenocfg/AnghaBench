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
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_pptdev {int bus; int slot; int func; } ;
typedef  int /*<<< orphan*/  pptdev ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BIND_PPTDEV ; 
 int /*<<< orphan*/  bzero (struct vm_pptdev*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_pptdev*) ; 

int
vm_assign_pptdev(struct vmctx *ctx, int bus, int slot, int func)
{
	struct vm_pptdev pptdev;

	bzero(&pptdev, sizeof(pptdev));
	pptdev.bus = bus;
	pptdev.slot = slot;
	pptdev.func = func;

	return (ioctl(ctx->fd, VM_BIND_PPTDEV, &pptdev));
}