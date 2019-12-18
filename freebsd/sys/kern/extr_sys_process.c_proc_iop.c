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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct uio {int uio_iovcnt; scalar_t__ uio_resid; int uio_rw; struct thread* uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_offset; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct proc {int dummy; } ;
struct iovec {size_t iov_len; scalar_t__ iov_base; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum uio_rw { ____Placeholder_uio_rw } uio_rw ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 size_t SSIZE_MAX ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  proc_rwmem (struct proc*,struct uio*) ; 

__attribute__((used)) static ssize_t
proc_iop(struct thread *td, struct proc *p, vm_offset_t va, void *buf,
    size_t len, enum uio_rw rw)
{
	struct iovec iov;
	struct uio uio;
	ssize_t slen;

	MPASS(len < SSIZE_MAX);
	slen = (ssize_t)len;

	iov.iov_base = (caddr_t)buf;
	iov.iov_len = len;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = va;
	uio.uio_resid = slen;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_rw = rw;
	uio.uio_td = td;
	proc_rwmem(p, &uio);
	if (uio.uio_resid == slen)
		return (-1);
	return (slen - uio.uio_resid);
}