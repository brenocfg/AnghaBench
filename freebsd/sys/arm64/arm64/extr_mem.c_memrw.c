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
typedef  struct vm_page* vm_page_t ;
typedef  int vm_offset_t ;
typedef  scalar_t__ u_int ;
struct vm_page {int /*<<< orphan*/  phys_addr; } ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_iovcnt; int uio_offset; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
#define  CDEV_MINOR_KMEM 129 
#define  CDEV_MINOR_MEM 128 
 int EFAULT ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_IN_DMAP (int) ; 
 int PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  VIRT_IN_DMAP (int) ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  kernacc (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_extract (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trunc_page (int) ; 
 int uiomove (void*,scalar_t__,struct uio*) ; 
 int /*<<< orphan*/  uiomove_fromphys (struct vm_page**,int,scalar_t__,struct uio*) ; 
 scalar_t__ ulmin (scalar_t__,scalar_t__) ; 

int
memrw(struct cdev *dev, struct uio *uio, int flags)
{
	struct iovec *iov;
	struct vm_page m;
	vm_page_t marr;
	vm_offset_t off, v;
	u_int cnt;
	int error;

	error = 0;

	while (uio->uio_resid > 0 && error == 0) {
		iov = uio->uio_iov;
		if (iov->iov_len == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			if (uio->uio_iovcnt < 0)
				panic("memrw");
			continue;
		}

		v = uio->uio_offset;
		off = v & PAGE_MASK;
		cnt = ulmin(iov->iov_len, PAGE_SIZE - (u_int)off);
		if (cnt == 0)
			continue;

		switch(dev2unit(dev)) {
		case CDEV_MINOR_KMEM:
			/* If the address is in the DMAP just copy it */
			if (VIRT_IN_DMAP(v)) {
				error = uiomove((void *)v, cnt, uio);
				break;
			}

			if (!kernacc((void *)v, cnt, uio->uio_rw == UIO_READ ?
			    VM_PROT_READ : VM_PROT_WRITE)) {
				error = EFAULT;
				break;
			}

			/* Get the physical address to read */
			v = pmap_extract(kernel_pmap, v);
			if (v == 0) {
				error = EFAULT;
				break;
			}

			/* FALLTHROUGH */
		case CDEV_MINOR_MEM:
			/* If within the DMAP use this to copy from */
			if (PHYS_IN_DMAP(v)) {
				v = PHYS_TO_DMAP(v);
				error = uiomove((void *)v, cnt, uio);
				break;
			}

			/* Have uiomove_fromphys handle the data */
			m.phys_addr = trunc_page(v);
			marr = &m;
			uiomove_fromphys(&marr, off, cnt, uio);
			break;
		}
	}

	return (error);
}