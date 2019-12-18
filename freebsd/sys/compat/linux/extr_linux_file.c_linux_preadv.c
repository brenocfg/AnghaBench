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
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct linux_preadv_args {int pos_l; int /*<<< orphan*/  fd; int /*<<< orphan*/  vlen; int /*<<< orphan*/  vec; scalar_t__ pos_h; } ;
typedef  int /*<<< orphan*/  offset ;
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int copyinuio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio**) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int kern_preadv (struct thread*,int /*<<< orphan*/ ,struct uio*,int) ; 
 int linux32_copyinuio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio**) ; 

int
linux_preadv(struct thread *td, struct linux_preadv_args *uap)
{
	struct uio *auio;
	int error;
	off_t offset;

	/*
	 * According http://man7.org/linux/man-pages/man2/preadv.2.html#NOTES
	 * pos_l and pos_h, respectively, contain the
	 * low order and high order 32 bits of offset.
	 */
	offset = (((off_t)uap->pos_h << (sizeof(offset) * 4)) <<
	    (sizeof(offset) * 4)) | uap->pos_l;
	if (offset < 0)
		return (EINVAL);
#ifdef COMPAT_LINUX32
	error = linux32_copyinuio(PTRIN(uap->vec), uap->vlen, &auio);
#else
	error = copyinuio(uap->vec, uap->vlen, &auio);
#endif
	if (error != 0)
		return (error);
	error = kern_preadv(td, uap->fd, auio, offset);
	free(auio, M_IOV);
	return (error);
}