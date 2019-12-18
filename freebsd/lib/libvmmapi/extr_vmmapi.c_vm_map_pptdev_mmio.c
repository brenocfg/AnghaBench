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
typedef  void* vm_paddr_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_pptdev_mmio {int bus; int slot; int func; size_t len; void* hpa; void* gpa; } ;
typedef  int /*<<< orphan*/  pptmmio ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_PPTDEV_MMIO ; 
 int /*<<< orphan*/  bzero (struct vm_pptdev_mmio*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_pptdev_mmio*) ; 

int
vm_map_pptdev_mmio(struct vmctx *ctx, int bus, int slot, int func,
		   vm_paddr_t gpa, size_t len, vm_paddr_t hpa)
{
	struct vm_pptdev_mmio pptmmio;

	bzero(&pptmmio, sizeof(pptmmio));
	pptmmio.bus = bus;
	pptmmio.slot = slot;
	pptmmio.func = func;
	pptmmio.gpa = gpa;
	pptmmio.len = len;
	pptmmio.hpa = hpa;

	return (ioctl(ctx->fd, VM_MAP_PPTDEV_MMIO, &pptmmio));
}