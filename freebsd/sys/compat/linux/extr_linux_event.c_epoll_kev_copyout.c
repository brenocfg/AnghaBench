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
struct linux_pemuldata {struct epoll_emuldata* epoll; } ;
struct kevent {int ident; } ;
struct epoll_event {int /*<<< orphan*/  data; } ;
struct epoll_emuldata {int fdc; int /*<<< orphan*/ * udata; } ;
struct epoll_copyout_args {int leventlist; int count; int error; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LINUX_PEM_SLOCK (struct linux_pemuldata*) ; 
 int /*<<< orphan*/  LINUX_PEM_SUNLOCK (struct linux_pemuldata*) ; 
 int /*<<< orphan*/  M_EPOLL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int copyout (struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  free (struct epoll_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_to_epoll (struct kevent*,struct epoll_event*) ; 
 struct epoll_event* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct linux_pemuldata* pem_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epoll_kev_copyout(void *arg, struct kevent *kevp, int count)
{
	struct epoll_copyout_args *args;
	struct linux_pemuldata *pem;
	struct epoll_emuldata *emd;
	struct epoll_event *eep;
	int error, fd, i;

	args = (struct epoll_copyout_args*) arg;
	eep = malloc(sizeof(*eep) * count, M_EPOLL, M_WAITOK | M_ZERO);

	pem = pem_find(args->p);
	KASSERT(pem != NULL, ("epoll proc emuldata not found.\n"));
	LINUX_PEM_SLOCK(pem);
	emd = pem->epoll;
	KASSERT(emd != NULL, ("epoll proc epolldata not found.\n"));

	for (i = 0; i < count; i++) {
		kevent_to_epoll(&kevp[i], &eep[i]);

		fd = kevp[i].ident;
		KASSERT(fd <= emd->fdc, ("epoll user data vector"
						    " is too small.\n"));
		eep[i].data = emd->udata[fd];
	}
	LINUX_PEM_SUNLOCK(pem);

	error = copyout(eep, args->leventlist, count * sizeof(*eep));
	if (error == 0) {
		args->leventlist += count;
		args->count += count;
	} else if (args->error == 0)
		args->error = error;

	free(eep, M_EPOLL);
	return (error);
}