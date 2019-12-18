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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  int /*<<< orphan*/  u_int ;
struct uio {scalar_t__ uio_rw; scalar_t__ uio_resid; scalar_t__ uio_offset; } ;
struct proc {TYPE_1__* p_vmspace; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PQ_ACTIVE ; 
 int /*<<< orphan*/  PROC_ASSERT_HELD (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_WRITE ; 
 int VM_FAULT_DIRTY ; 
 int VM_FAULT_NORMAL ; 
 int VM_PROT_COPY ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 int trunc_page (int) ; 
 int uiomove_fromphys (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct uio*) ; 
 int vm_fault (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_check_protection (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_unlock_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_sync_icache (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
proc_rwmem(struct proc *p, struct uio *uio)
{
	vm_map_t map;
	vm_offset_t pageno;		/* page number */
	vm_prot_t reqprot;
	int error, fault_flags, page_offset, writing;

	/*
	 * Assert that someone has locked this vmspace.  (Should be
	 * curthread but we can't assert that.)  This keeps the process
	 * from exiting out from under us until this operation completes.
	 */
	PROC_ASSERT_HELD(p);
	PROC_LOCK_ASSERT(p, MA_NOTOWNED);

	/*
	 * The map we want...
	 */
	map = &p->p_vmspace->vm_map;

	/*
	 * If we are writing, then we request vm_fault() to create a private
	 * copy of each page.  Since these copies will not be writeable by the
	 * process, we must explicity request that they be dirtied.
	 */
	writing = uio->uio_rw == UIO_WRITE;
	reqprot = writing ? VM_PROT_COPY | VM_PROT_READ : VM_PROT_READ;
	fault_flags = writing ? VM_FAULT_DIRTY : VM_FAULT_NORMAL;

	/*
	 * Only map in one page at a time.  We don't have to, but it
	 * makes things easier.  This way is trivial - right?
	 */
	do {
		vm_offset_t uva;
		u_int len;
		vm_page_t m;

		uva = (vm_offset_t)uio->uio_offset;

		/*
		 * Get the page number of this segment.
		 */
		pageno = trunc_page(uva);
		page_offset = uva - pageno;

		/*
		 * How many bytes to copy
		 */
		len = min(PAGE_SIZE - page_offset, uio->uio_resid);

		/*
		 * Fault and hold the page on behalf of the process.
		 */
		error = vm_fault(map, pageno, reqprot, fault_flags, &m);
		if (error != KERN_SUCCESS) {
			if (error == KERN_RESOURCE_SHORTAGE)
				error = ENOMEM;
			else
				error = EFAULT;
			break;
		}

		/*
		 * Now do the i/o move.
		 */
		error = uiomove_fromphys(&m, page_offset, len, uio);

		/* Make the I-cache coherent for breakpoints. */
		if (writing && error == 0) {
			vm_map_lock_read(map);
			if (vm_map_check_protection(map, pageno, pageno +
			    PAGE_SIZE, VM_PROT_EXECUTE))
				vm_sync_icache(map, uva, len);
			vm_map_unlock_read(map);
		}

		/*
		 * Release the page.
		 */
		vm_page_unwire(m, PQ_ACTIVE);

	} while (error == 0 && uio->uio_resid > 0);

	return (error);
}