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
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct kevent_copyops {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_KQUEUE_CHANGE ; 
 int /*<<< orphan*/  CAP_KQUEUE_EVENT ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_rights_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int kern_kevent_fp (struct thread*,struct file*,int,int,struct kevent_copyops*,struct timespec const*) ; 

int
kern_kevent(struct thread *td, int fd, int nchanges, int nevents,
    struct kevent_copyops *k_ops, const struct timespec *timeout)
{
	cap_rights_t rights;
	struct file *fp;
	int error;

	cap_rights_init(&rights);
	if (nchanges > 0)
		cap_rights_set(&rights, CAP_KQUEUE_CHANGE);
	if (nevents > 0)
		cap_rights_set(&rights, CAP_KQUEUE_EVENT);
	error = fget(td, fd, &rights, &fp);
	if (error != 0)
		return (error);

	error = kern_kevent_fp(td, fp, nchanges, nevents, k_ops, timeout);
	fdrop(fp, td);

	return (error);
}