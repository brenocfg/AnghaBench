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
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sel; int /*<<< orphan*/  devq; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__ devsoftc ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
devpoll(struct cdev *dev, int events, struct thread *td)
{
	int	revents = 0;

	mtx_lock(&devsoftc.mtx);
	if (events & (POLLIN | POLLRDNORM)) {
		if (!TAILQ_EMPTY(&devsoftc.devq))
			revents = events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &devsoftc.sel);
	}
	mtx_unlock(&devsoftc.mtx);

	return (revents);
}