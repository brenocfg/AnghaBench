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
struct vm_guest_paging {int dummy; } ;
struct vm_gla2gpa {int vcpuid; int prot; int fault; int /*<<< orphan*/  gpa; struct vm_guest_paging paging; int /*<<< orphan*/  gla; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GLA2GPA_NOFAULT ; 
 int /*<<< orphan*/  bzero (struct vm_gla2gpa*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_gla2gpa*) ; 

int
vm_gla2gpa_nofault(struct vmctx *ctx, int vcpu, struct vm_guest_paging *paging,
    uint64_t gla, int prot, uint64_t *gpa, int *fault)
{
	struct vm_gla2gpa gg;
	int error;

	bzero(&gg, sizeof(struct vm_gla2gpa));
	gg.vcpuid = vcpu;
	gg.prot = prot;
	gg.gla = gla;
	gg.paging = *paging;

	error = ioctl(ctx->fd, VM_GLA2GPA_NOFAULT, &gg);
	if (error == 0) {
		*fault = gg.fault;
		*gpa = gg.gpa;
	}
	return (error);
}