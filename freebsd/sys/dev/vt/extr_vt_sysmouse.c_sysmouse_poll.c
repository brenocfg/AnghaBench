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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysmouse_bufpoll ; 
 scalar_t__ sysmouse_length ; 
 int /*<<< orphan*/  sysmouse_lock ; 

__attribute__((used)) static int
sysmouse_poll(struct cdev *dev, int events, struct thread *td)
{
	int revents = 0;

	mtx_lock(&sysmouse_lock);
	if (events & (POLLIN|POLLRDNORM)) {
		if (sysmouse_length > 0)
			revents = events & (POLLIN|POLLRDNORM);
		else
			selrecord(td, &sysmouse_bufpoll);
	}
	mtx_unlock(&sysmouse_lock);

	return (revents);
}