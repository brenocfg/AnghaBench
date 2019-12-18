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
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct linux_pemuldata {struct epoll_emuldata* epoll; } ;
struct epoll_emuldata {int fdc; int /*<<< orphan*/ * udata; } ;
typedef  int /*<<< orphan*/  epoll_udata_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_SIZE (int) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINUX_PEM_XLOCK (struct linux_pemuldata*) ; 
 int /*<<< orphan*/  LINUX_PEM_XUNLOCK (struct linux_pemuldata*) ; 
 int /*<<< orphan*/  M_EPOLL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct epoll_emuldata* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct linux_pemuldata* pem_find (struct proc*) ; 
 struct epoll_emuldata* realloc (struct epoll_emuldata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
epoll_fd_install(struct thread *td, int fd, epoll_udata_t udata)
{
	struct linux_pemuldata *pem;
	struct epoll_emuldata *emd;
	struct proc *p;

	p = td->td_proc;

	pem = pem_find(p);
	KASSERT(pem != NULL, ("epoll proc emuldata not found.\n"));

	LINUX_PEM_XLOCK(pem);
	if (pem->epoll == NULL) {
		emd = malloc(EPOLL_SIZE(fd), M_EPOLL, M_WAITOK);
		emd->fdc = fd;
		pem->epoll = emd;
	} else {
		emd = pem->epoll;
		if (fd > emd->fdc) {
			emd = realloc(emd, EPOLL_SIZE(fd), M_EPOLL, M_WAITOK);
			emd->fdc = fd;
			pem->epoll = emd;
		}
	}
	emd->udata[fd] = udata;
	LINUX_PEM_XUNLOCK(pem);
}