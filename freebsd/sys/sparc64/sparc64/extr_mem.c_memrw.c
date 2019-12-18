#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint32_t ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_iovcnt; scalar_t__ uio_offset; scalar_t__ uio_rw; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct cdev {int dummy; } ;
struct TYPE_5__ {int color; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 scalar_t__ CDEV_MINOR_KMEM ; 
 scalar_t__ CDEV_MINOR_MEM ; 
 scalar_t__ DCACHE_COLORS ; 
 int EFAULT ; 
 int ENOMEM ; 
 scalar_t__ FALSE ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ TLB_PHYS_TO_DIRECT (scalar_t__) ; 
 scalar_t__ UIO_READ ; 
 scalar_t__ VM_MIN_DIRECT_ADDRESS ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 scalar_t__ dcache_color_ignore ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  is_physical_memory (scalar_t__) ; 
 scalar_t__ kernacc (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kva_alloc (scalar_t__) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,TYPE_2__**,int) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int uiomove (void*,scalar_t__,struct uio*) ; 
 scalar_t__ ulmin (scalar_t__,scalar_t__) ; 
 TYPE_2__* vm_phys_paddr_to_vm_page (scalar_t__) ; 

int
memrw(struct cdev *dev, struct uio *uio, int flags)
{
	struct iovec *iov;
	vm_offset_t eva;
	vm_offset_t off;
	vm_offset_t ova;
	vm_offset_t va;
	vm_prot_t prot;
	vm_paddr_t pa;
	vm_size_t cnt;
	vm_page_t m;
	int error;
	uint32_t colors;

	cnt = 0;
	colors = 1;
	error = 0;
	ova = 0;

	while (uio->uio_resid > 0 && error == 0) {
		iov = uio->uio_iov;
		if (iov->iov_len == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			if (uio->uio_iovcnt < 0)
				panic("memrw");
			continue;
		}
		if (dev2unit(dev) == CDEV_MINOR_MEM) {
			pa = uio->uio_offset & ~PAGE_MASK;
			if (!is_physical_memory(pa)) {
				error = EFAULT;
				break;
			}

			off = uio->uio_offset & PAGE_MASK;
			cnt = PAGE_SIZE - ((vm_offset_t)iov->iov_base &
			    PAGE_MASK);
			cnt = ulmin(cnt, PAGE_SIZE - off);
			cnt = ulmin(cnt, iov->iov_len);

			m = vm_phys_paddr_to_vm_page(pa);
			if (m != NULL) {
				if (ova == 0) {
					if (dcache_color_ignore == 0)
						colors = DCACHE_COLORS;
					ova = kva_alloc(PAGE_SIZE * colors);
					if (ova == 0) {
						error = ENOMEM;
						break;
					}
				}
				if (colors != 1 && m->md.color != -1)
					va = ova + m->md.color * PAGE_SIZE;
				else
					va = ova;
				pmap_qenter(va, &m, 1);
				error = uiomove((void *)(va + off), cnt,
				    uio);
				pmap_qremove(va, 1);
			} else {
				va = TLB_PHYS_TO_DIRECT(pa);
				error = uiomove((void *)(va + off), cnt,
				    uio);
			}
			break;
		} else if (dev2unit(dev) == CDEV_MINOR_KMEM) {
			va = trunc_page(uio->uio_offset);
			eva = round_page(uio->uio_offset + iov->iov_len);

			/*
			 * Make sure that all of the pages are currently
			 * resident so we don't create any zero fill pages.
			 */
			for (; va < eva; va += PAGE_SIZE)
				if (pmap_kextract(va) == 0)
					return (EFAULT);

			prot = (uio->uio_rw == UIO_READ) ? VM_PROT_READ :
			    VM_PROT_WRITE;
			va = uio->uio_offset;
			if (va < VM_MIN_DIRECT_ADDRESS &&
			    kernacc((void *)va, iov->iov_len, prot) == FALSE)
				return (EFAULT);

			error = uiomove((void *)va, iov->iov_len, uio);
			break;
		}
		/* else panic! */
	}
	if (ova != 0)
		kva_free(ova, PAGE_SIZE * colors);
	return (error);
}