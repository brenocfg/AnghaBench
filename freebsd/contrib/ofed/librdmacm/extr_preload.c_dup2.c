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
struct fd_info {scalar_t__ state; int dupfd; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {int (* dup2 ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 struct fd_info* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fd_fork_active ; 
 scalar_t__ fd_fork_passive ; 
 int /*<<< orphan*/  fork_active (int) ; 
 int /*<<< orphan*/  fork_passive (int) ; 
 int /*<<< orphan*/  idm ; 
 struct fd_info* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idm_set (int /*<<< orphan*/ *,int,struct fd_info*) ; 
 int /*<<< orphan*/  init_preload () ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ real ; 
 int stub1 (int,int) ; 

int dup2(int oldfd, int newfd)
{
	struct fd_info *oldfdi, *newfdi;
	int ret;

	init_preload();
	oldfdi = idm_lookup(&idm, oldfd);
	if (oldfdi) {
		if (oldfdi->state == fd_fork_passive)
			fork_passive(oldfd);
		else if (oldfdi->state == fd_fork_active)
			fork_active(oldfd);
	}

	newfdi = idm_lookup(&idm, newfd);
	if (newfdi) {
		 /* newfd cannot have been dup'ed directly */
		if (atomic_load(&newfdi->refcnt) > 1)
			return ERR(EBUSY);
		close(newfd);
	}

	ret = real.dup2(oldfd, newfd);
	if (!oldfdi || ret != newfd)
		return ret;

	newfdi = calloc(1, sizeof(*newfdi));
	if (!newfdi) {
		close(newfd);
		return ERR(ENOMEM);
	}

	pthread_mutex_lock(&mut);
	idm_set(&idm, newfd, newfdi);
	pthread_mutex_unlock(&mut);

	newfdi->fd = oldfdi->fd;
	newfdi->type = oldfdi->type;
	if (oldfdi->dupfd != -1) {
		newfdi->dupfd = oldfdi->dupfd;
		oldfdi = idm_lookup(&idm, oldfdi->dupfd);
	} else {
		newfdi->dupfd = oldfd;
	}
	atomic_store(&newfdi->refcnt, 1);
	atomic_fetch_add(&oldfdi->refcnt, 1);
	return newfd;
}