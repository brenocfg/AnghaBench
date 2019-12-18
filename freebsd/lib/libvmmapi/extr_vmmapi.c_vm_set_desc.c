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
typedef  int /*<<< orphan*/  vmsegdesc ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {void* access; void* limit; int /*<<< orphan*/  base; } ;
struct vm_seg_desc {int cpuid; int regnum; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_SET_SEGMENT_DESCRIPTOR ; 
 int /*<<< orphan*/  bzero (struct vm_seg_desc*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_seg_desc*) ; 

int
vm_set_desc(struct vmctx *ctx, int vcpu, int reg,
	    uint64_t base, uint32_t limit, uint32_t access)
{
	int error;
	struct vm_seg_desc vmsegdesc;

	bzero(&vmsegdesc, sizeof(vmsegdesc));
	vmsegdesc.cpuid = vcpu;
	vmsegdesc.regnum = reg;
	vmsegdesc.desc.base = base;
	vmsegdesc.desc.limit = limit;
	vmsegdesc.desc.access = access;

	error = ioctl(ctx->fd, VM_SET_SEGMENT_DESCRIPTOR, &vmsegdesc);
	return (error);
}