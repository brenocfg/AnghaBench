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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_paddr_t ;
struct uio {int uio_iovcnt; size_t uio_resid; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct iovec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int PHYS_PAGE_COUNT (size_t) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int uiomove_fromphys (int /*<<< orphan*/ *,int,size_t,struct uio*) ; 

int
physcopyout(vm_paddr_t src, void *dst, size_t len)
{
	vm_page_t m[PHYS_PAGE_COUNT(len)];
	struct iovec iov[1];
	struct uio uio;
	int i;

	iov[0].iov_base = dst;
	iov[0].iov_len = len;
	uio.uio_iov = iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = 0;
	uio.uio_resid = len;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_rw = UIO_READ;
	for (i = 0; i < PHYS_PAGE_COUNT(len); i++, src += PAGE_SIZE)
		m[i] = PHYS_TO_VM_PAGE(src);
	return (uiomove_fromphys(m, src & PAGE_MASK, len, &uio));
}