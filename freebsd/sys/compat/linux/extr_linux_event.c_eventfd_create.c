#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {int* td_retval; TYPE_1__* td_proc; } ;
struct filedesc {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct eventfd {int efd_flags; int /*<<< orphan*/  efd_lock; TYPE_2__ efd_sel; int /*<<< orphan*/  efd_count; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_LINUXEFD ; 
 int FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
 int LINUX_O_CLOEXEC ; 
 int LINUX_O_NONBLOCK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_EPOLL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int O_CLOEXEC ; 
 int /*<<< orphan*/  eventfdops ; 
 int falloc (struct thread*,struct file**,int*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct eventfd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct eventfd* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eventfd_create(struct thread *td, uint32_t initval, int flags)
{
	struct filedesc *fdp;
	struct eventfd *efd;
	struct file *fp;
	int fflags, fd, error;

	fflags = 0;
	if ((flags & LINUX_O_CLOEXEC) != 0)
		fflags |= O_CLOEXEC;

	fdp = td->td_proc->p_fd;
	error = falloc(td, &fp, &fd, fflags);
	if (error != 0)
		return (error);

	efd = malloc(sizeof(*efd), M_EPOLL, M_WAITOK | M_ZERO);
	efd->efd_flags = flags;
	efd->efd_count = initval;
	mtx_init(&efd->efd_lock, "eventfd", NULL, MTX_DEF);

	knlist_init_mtx(&efd->efd_sel.si_note, &efd->efd_lock);

	fflags = FREAD | FWRITE;
	if ((flags & LINUX_O_NONBLOCK) != 0)
		fflags |= FNONBLOCK;

	finit(fp, fflags, DTYPE_LINUXEFD, efd, &eventfdops);
	fdrop(fp, td);

	td->td_retval[0] = fd;
	return (error);
}