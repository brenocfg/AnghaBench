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
struct mqueue {int dummy; } ;
struct kmq_timedreceive_args {int /*<<< orphan*/  msg_prio; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg_ptr; int /*<<< orphan*/ * abs_timeout; int /*<<< orphan*/  mqd; } ;
struct file {int f_flag; } ;
typedef  int /*<<< orphan*/  ets ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int O_NONBLOCK ; 
 int copyin (int /*<<< orphan*/ *,struct timespec*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getmq_read (struct thread*,int /*<<< orphan*/ ,struct file**,int /*<<< orphan*/ *,struct mqueue**) ; 
 int mqueue_receive (struct mqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct timespec*) ; 

int
sys_kmq_timedreceive(struct thread *td, struct kmq_timedreceive_args *uap)
{
	struct mqueue *mq;
	struct file *fp;
	struct timespec *abs_timeout, ets;
	int error;
	int waitok;

	AUDIT_ARG_FD(uap->mqd);
	error = getmq_read(td, uap->mqd, &fp, NULL, &mq);
	if (error)
		return (error);
	if (uap->abs_timeout != NULL) {
		error = copyin(uap->abs_timeout, &ets, sizeof(ets));
		if (error != 0)
			goto out;
		abs_timeout = &ets;
	} else
		abs_timeout = NULL;
	waitok = !(fp->f_flag & O_NONBLOCK);
	error = mqueue_receive(mq, uap->msg_ptr, uap->msg_len,
		uap->msg_prio, waitok, abs_timeout);
out:
	fdrop(fp, td);
	return (error);
}