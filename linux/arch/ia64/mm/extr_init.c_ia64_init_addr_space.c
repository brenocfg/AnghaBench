#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; void* vm_end; } ;
struct TYPE_5__ {int rbs_bot; } ;
struct TYPE_7__ {int personality; TYPE_2__* mm; TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int MMAP_PAGE_ZERO ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 void* PAGE_SIZE ; 
 int VM_ACCOUNT ; 
 int VM_DATA_DEFAULT_FLAGS ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_GROWSUP ; 
 int VM_IO ; 
 int VM_MAYREAD ; 
 int VM_READ ; 
 int _PAGE_MA_NAT ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_set_rbs_bot () ; 
 scalar_t__ insert_vm_struct (TYPE_2__*,struct vm_area_struct*) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* vm_area_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_area_free (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_get_page_prot (int) ; 
 int /*<<< orphan*/  vma_set_anonymous (struct vm_area_struct*) ; 

void
ia64_init_addr_space (void)
{
	struct vm_area_struct *vma;

	ia64_set_rbs_bot();

	/*
	 * If we're out of memory and kmem_cache_alloc() returns NULL, we simply ignore
	 * the problem.  When the process attempts to write to the register backing store
	 * for the first time, it will get a SEGFAULT in this case.
	 */
	vma = vm_area_alloc(current->mm);
	if (vma) {
		vma_set_anonymous(vma);
		vma->vm_start = current->thread.rbs_bot & PAGE_MASK;
		vma->vm_end = vma->vm_start + PAGE_SIZE;
		vma->vm_flags = VM_DATA_DEFAULT_FLAGS|VM_GROWSUP|VM_ACCOUNT;
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
		down_write(&current->mm->mmap_sem);
		if (insert_vm_struct(current->mm, vma)) {
			up_write(&current->mm->mmap_sem);
			vm_area_free(vma);
			return;
		}
		up_write(&current->mm->mmap_sem);
	}

	/* map NaT-page at address zero to speed up speculative dereferencing of NULL: */
	if (!(current->personality & MMAP_PAGE_ZERO)) {
		vma = vm_area_alloc(current->mm);
		if (vma) {
			vma_set_anonymous(vma);
			vma->vm_end = PAGE_SIZE;
			vma->vm_page_prot = __pgprot(pgprot_val(PAGE_READONLY) | _PAGE_MA_NAT);
			vma->vm_flags = VM_READ | VM_MAYREAD | VM_IO |
					VM_DONTEXPAND | VM_DONTDUMP;
			down_write(&current->mm->mmap_sem);
			if (insert_vm_struct(current->mm, vma)) {
				up_write(&current->mm->mmap_sem);
				vm_area_free(vma);
				return;
			}
			up_write(&current->mm->mmap_sem);
		}
	}
}