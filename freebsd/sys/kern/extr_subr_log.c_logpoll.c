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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_selp; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 TYPE_1__ logsoftc ; 
 scalar_t__ msgbuf_getcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  msgbufp ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
logpoll(struct cdev *dev, int events, struct thread *td)
{
	int revents = 0;

	if (events & (POLLIN | POLLRDNORM)) {
		mtx_lock(&msgbuf_lock);
		if (msgbuf_getcount(msgbufp) > 0)
			revents |= events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &logsoftc.sc_selp);
		mtx_unlock(&msgbuf_lock);
	}
	return (revents);
}