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
typedef  int /*<<< orphan*/ * vm_object_t ;
struct vm {struct mem_seg* mem_segs; } ;
struct mem_seg {size_t len; int sysmem; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 int VM_MAX_MEMSEGS ; 
 int /*<<< orphan*/ * vm_object_allocate (int /*<<< orphan*/ ,size_t) ; 

int
vm_alloc_memseg(struct vm *vm, int ident, size_t len, bool sysmem)
{
	struct mem_seg *seg;
	vm_object_t obj;

	if (ident < 0 || ident >= VM_MAX_MEMSEGS)
		return (EINVAL);

	if (len == 0 || (len & PAGE_MASK))
		return (EINVAL);

	seg = &vm->mem_segs[ident];
	if (seg->object != NULL) {
		if (seg->len == len && seg->sysmem == sysmem)
			return (EEXIST);
		else
			return (EINVAL);
	}

	obj = vm_object_allocate(OBJT_DEFAULT, len >> PAGE_SHIFT);
	if (obj == NULL)
		return (ENOMEM);

	seg->len = len;
	seg->object = obj;
	seg->sysmem = sysmem;
	return (0);
}