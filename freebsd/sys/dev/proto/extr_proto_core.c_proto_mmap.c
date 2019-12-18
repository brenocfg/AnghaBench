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
typedef  int vm_paddr_t ;
typedef  int vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_2__ {int /*<<< orphan*/  busdma; int /*<<< orphan*/  res; } ;
struct proto_res {int r_type; int r_size; TYPE_1__ r_d; } ;
struct cdev {struct proto_res* si_drv2; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENXIO ; 
 int PAGE_MASK ; 
#define  PROTO_RES_BUSDMA 129 
 int PROT_EXEC ; 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  proto_busdma_mmap_allowed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_mmap(struct cdev *cdev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	struct proto_res *r;

	if (offset & PAGE_MASK)
		return (EINVAL);
	if (prot & PROT_EXEC)
		return (EACCES);

	r = cdev->si_drv2;

	switch (r->r_type) {
	case SYS_RES_MEMORY:
		if (offset >= r->r_size)
			return (EINVAL);
		*paddr = rman_get_start(r->r_d.res) + offset;
#ifndef __sparc64__
		*memattr = VM_MEMATTR_UNCACHEABLE;
#endif
		break;
	case PROTO_RES_BUSDMA:
		if (!proto_busdma_mmap_allowed(r->r_d.busdma, offset))
			return (EINVAL);
		*paddr = offset;
		break;
	default:
		return (ENXIO);
	}
	return (0);
}