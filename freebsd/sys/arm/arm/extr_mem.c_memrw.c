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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_int ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_iovcnt; scalar_t__ uio_offset; scalar_t__ uio_rw; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ CDEV_MINOR_KMEM ; 
 scalar_t__ CDEV_MINOR_MEM ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ UIO_READ ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/ * _tmppt ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 scalar_t__* dump_avail ; 
 int /*<<< orphan*/  kernacc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_extract (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_kenter (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 int /*<<< orphan*/  pmap_tlb_flush (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmppt_lock ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

int
memrw(struct cdev *dev, struct uio *uio, int flags)
{
	int o;
	u_int c = 0, v;
	struct iovec *iov;
	int error = 0;
	vm_offset_t addr, eaddr;

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
			int i;
			int address_valid = 0;

			v = uio->uio_offset;
			v &= ~PAGE_MASK;
			for (i = 0; dump_avail[i] || dump_avail[i + 1];
			i += 2) {
				if (v >= dump_avail[i] &&
				    v < dump_avail[i + 1]) {
					address_valid = 1;
					break;
				}
			}
			if (!address_valid)
				return (EINVAL);
			sx_xlock(&tmppt_lock);
			pmap_kenter((vm_offset_t)_tmppt, v);
#if __ARM_ARCH >= 6
			pmap_tlb_flush(kernel_pmap, (vm_offset_t)_tmppt);
#endif
			o = (int)uio->uio_offset & PAGE_MASK;
			c = (u_int)(PAGE_SIZE - ((int)iov->iov_base & PAGE_MASK));
			c = min(c, (u_int)(PAGE_SIZE - o));
			c = min(c, (u_int)iov->iov_len);
			error = uiomove((caddr_t)&_tmppt[o], (int)c, uio);
			pmap_qremove((vm_offset_t)_tmppt, 1);
			sx_xunlock(&tmppt_lock);
			continue;
		}
		else if (dev2unit(dev) == CDEV_MINOR_KMEM) {
			c = iov->iov_len;

			/*
			 * Make sure that all of the pages are currently
			 * resident so that we don't create any zero-fill
			 * pages.
			 */
			addr = trunc_page(uio->uio_offset);
			eaddr = round_page(uio->uio_offset + c);

			for (; addr < eaddr; addr += PAGE_SIZE)
				if (pmap_extract(kernel_pmap, addr) == 0)
					return (EFAULT);
			if (!kernacc((caddr_t)(int)uio->uio_offset, c,
			    uio->uio_rw == UIO_READ ?
			    VM_PROT_READ : VM_PROT_WRITE))
					return (EFAULT);
			error = uiomove((caddr_t)(int)uio->uio_offset, (int)c, uio);
			continue;
		}
		/* else panic! */
	}
	return (error);
}