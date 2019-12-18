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
struct uio {int uio_iovcnt; size_t uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_offset; struct iovec* uio_iov; } ;
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct iovec {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHOLD (struct proc*) ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct thread* curthread ; 
 int proc_rwmem (struct proc*,struct uio*) ; 

__attribute__((used)) static int
cuse_proc2proc_copy(struct proc *proc_s, vm_offset_t data_s,
    struct proc *proc_d, vm_offset_t data_d, size_t len)
{
	struct thread *td;
	struct proc *proc_cur;
	int error;

	td = curthread;
	proc_cur = td->td_proc;

	if (proc_cur == proc_d) {
		struct iovec iov = {
			.iov_base = (caddr_t)data_d,
			.iov_len = len,
		};
		struct uio uio = {
			.uio_iov = &iov,
			.uio_iovcnt = 1,
			.uio_offset = (off_t)data_s,
			.uio_resid = len,
			.uio_segflg = UIO_USERSPACE,
			.uio_rw = UIO_READ,
			.uio_td = td,
		};

		PHOLD(proc_s);
		error = proc_rwmem(proc_s, &uio);
		PRELE(proc_s);

	} else if (proc_cur == proc_s) {
		struct iovec iov = {
			.iov_base = (caddr_t)data_s,
			.iov_len = len,
		};
		struct uio uio = {
			.uio_iov = &iov,
			.uio_iovcnt = 1,
			.uio_offset = (off_t)data_d,
			.uio_resid = len,
			.uio_segflg = UIO_USERSPACE,
			.uio_rw = UIO_WRITE,
			.uio_td = td,
		};

		PHOLD(proc_d);
		error = proc_rwmem(proc_d, &uio);
		PRELE(proc_d);
	} else {
		error = EINVAL;
	}
	return (error);
}