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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_intinfo {int vcpuid; int /*<<< orphan*/  info2; int /*<<< orphan*/  info1; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_INTINFO ; 
 int /*<<< orphan*/  bzero (struct vm_intinfo*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_intinfo*) ; 

int
vm_get_intinfo(struct vmctx *ctx, int vcpu, uint64_t *info1, uint64_t *info2)
{
	struct vm_intinfo vmii;
	int error;

	bzero(&vmii, sizeof(struct vm_intinfo));
	vmii.vcpuid = vcpu;
	error = ioctl(ctx->fd, VM_GET_INTINFO, &vmii);
	if (error == 0) {
		*info1 = vmii.info1;
		*info2 = vmii.info2;
	}
	return (error);
}