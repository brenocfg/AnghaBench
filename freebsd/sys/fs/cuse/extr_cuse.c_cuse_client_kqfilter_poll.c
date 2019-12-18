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
struct cuse_client {int cflags; int /*<<< orphan*/  server; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CUSE_CLI_KNOTE_HAS_READ ; 
 int CUSE_CLI_KNOTE_HAS_WRITE ; 
 int CUSE_CLI_KNOTE_NEED_READ ; 
 int CUSE_CLI_KNOTE_NEED_WRITE ; 
 int POLLIN ; 
 int POLLOUT ; 
 int cuse_client_poll (struct cdev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_server_wakeup_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_unlock () ; 

__attribute__((used)) static void
cuse_client_kqfilter_poll(struct cdev *dev, struct cuse_client *pcc)
{
	int temp;

	cuse_lock();
	temp = (pcc->cflags & (CUSE_CLI_KNOTE_HAS_READ |
	    CUSE_CLI_KNOTE_HAS_WRITE));
	pcc->cflags &= ~(CUSE_CLI_KNOTE_NEED_READ |
	    CUSE_CLI_KNOTE_NEED_WRITE);
	cuse_unlock();

	if (temp != 0) {
		/* get the latest polling state from the server */
		temp = cuse_client_poll(dev, POLLIN | POLLOUT, NULL);

		if (temp & (POLLIN | POLLOUT)) {
			cuse_lock();
			if (temp & POLLIN)
				pcc->cflags |= CUSE_CLI_KNOTE_NEED_READ;
			if (temp & POLLOUT)
				pcc->cflags |= CUSE_CLI_KNOTE_NEED_WRITE;

			/* make sure the "knote" gets woken up */
			cuse_server_wakeup_locked(pcc->server);
			cuse_unlock();
		}
	}
}