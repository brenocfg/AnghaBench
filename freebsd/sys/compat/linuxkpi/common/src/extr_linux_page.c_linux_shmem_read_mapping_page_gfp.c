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
typedef  struct page* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_NOWAIT ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PAGER_OK ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vm_page_grab_valid (struct page**,int /*<<< orphan*/ ,int,int) ; 

struct page *
linux_shmem_read_mapping_page_gfp(vm_object_t obj, int pindex, gfp_t gfp)
{
	vm_page_t page;
	int rv;

	if ((gfp & GFP_NOWAIT) != 0)
		panic("GFP_NOWAIT is unimplemented");

	VM_OBJECT_WLOCK(obj);
	rv = vm_page_grab_valid(&page, obj, pindex, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOBUSY | VM_ALLOC_WIRED);
	VM_OBJECT_WUNLOCK(obj);
	if (rv != VM_PAGER_OK)
		return (ERR_PTR(-EINVAL));
	return (page);
}