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
struct uio {int uio_resid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {scalar_t__ f_type; int f_flag; struct eventfd* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct eventfd {int efd_count; int efd_flags; int /*<<< orphan*/  efd_lock; TYPE_1__ efd_sel; } ;
typedef  int eventfd_t ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXEFD ; 
 int EAGAIN ; 
 int EINVAL ; 
 int FNONBLOCK ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LINUX_EFD_SEMAPHORE ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_sleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int uiomove (int*,int,struct uio*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static int
eventfd_read(struct file *fp, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{
	struct eventfd *efd;
	eventfd_t count;
	int error;

	efd = fp->f_data;
	if (fp->f_type != DTYPE_LINUXEFD || efd == NULL)
		return (EINVAL);

	if (uio->uio_resid < sizeof(eventfd_t))
		return (EINVAL);

	error = 0;
	mtx_lock(&efd->efd_lock);
retry:
	if (efd->efd_count == 0) {
		if ((fp->f_flag & FNONBLOCK) != 0) {
			mtx_unlock(&efd->efd_lock);
			return (EAGAIN);
		}
		error = mtx_sleep(&efd->efd_count, &efd->efd_lock, PCATCH, "lefdrd", 0);
		if (error == 0)
			goto retry;
	}
	if (error == 0) {
		if ((efd->efd_flags & LINUX_EFD_SEMAPHORE) != 0) {
			count = 1;
			--efd->efd_count;
		} else {
			count = efd->efd_count;
			efd->efd_count = 0;
		}
		KNOTE_LOCKED(&efd->efd_sel.si_note, 0);
		selwakeup(&efd->efd_sel);
		wakeup(&efd->efd_count);
		mtx_unlock(&efd->efd_lock);
		error = uiomove(&count, sizeof(eventfd_t), uio);
	} else
		mtx_unlock(&efd->efd_lock);

	return (error);
}