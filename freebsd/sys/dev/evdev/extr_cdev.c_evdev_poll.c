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
struct thread {int /*<<< orphan*/  td_tid; } ;
struct evdev_client {int ec_selected; int /*<<< orphan*/  ec_selp; scalar_t__ ec_revoked; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_CLIENT_EMPTYQ (struct evdev_client*) ; 
 int /*<<< orphan*/  EVDEV_CLIENT_LOCKQ (struct evdev_client*) ; 
 int /*<<< orphan*/  EVDEV_CLIENT_UNLOCKQ (struct evdev_client*) ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  debugf (struct evdev_client*,char*,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evdev_poll(struct cdev *dev, int events, struct thread *td)
{
	struct evdev_client *client;
	int ret;
	int revents = 0;

	ret = devfs_get_cdevpriv((void **)&client);
	if (ret != 0)
		return (POLLNVAL);

	debugf(client, "poll by thread %d", td->td_tid);

	if (client->ec_revoked)
		return (POLLHUP);

	if (events & (POLLIN | POLLRDNORM)) {
		EVDEV_CLIENT_LOCKQ(client);
		if (!EVDEV_CLIENT_EMPTYQ(client))
			revents = events & (POLLIN | POLLRDNORM);
		else {
			client->ec_selected = true;
			selrecord(td, &client->ec_selp);
		}
		EVDEV_CLIENT_UNLOCKQ(client);
	}

	return (revents);
}