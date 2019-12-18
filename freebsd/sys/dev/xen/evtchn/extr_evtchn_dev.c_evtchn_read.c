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
struct uio {int uio_resid; } ;
struct per_user_data {unsigned int ring_cons; unsigned int ring_prod; int /*<<< orphan*/  ring_cons_mutex; int /*<<< orphan*/ * ring; scalar_t__ ring_overflow; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int EFAULT ; 
 int EFBIG ; 
 int EINVAL ; 
 size_t EVTCHN_RING_MASK (unsigned int) ; 
 unsigned int EVTCHN_RING_SIZE ; 
 int EWOULDBLOCK ; 
 int IO_NDELAY ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCATCH ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  rmb () ; 
 int sx_sleep (struct per_user_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uiomove (int /*<<< orphan*/ *,unsigned int,struct uio*) ; 

__attribute__((used)) static int
evtchn_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int error, count;
	unsigned int c, p, bytes1 = 0, bytes2 = 0;
	struct per_user_data *u;

	error = devfs_get_cdevpriv((void **)&u);
	if (error != 0)
		return (EINVAL);

	/* Whole number of ports. */
	count = uio->uio_resid;
	count &= ~(sizeof(evtchn_port_t)-1);

	if (count == 0)
		return (0);

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;

	sx_xlock(&u->ring_cons_mutex);
	for (;;) {
		error = EFBIG;
		if (u->ring_overflow)
			goto unlock_out;

		c = u->ring_cons;
		p = u->ring_prod;
		if (c != p)
			break;

		if (ioflag & IO_NDELAY) {
			sx_xunlock(&u->ring_cons_mutex);
			return (EWOULDBLOCK);
		}

		error = sx_sleep(u, &u->ring_cons_mutex, PCATCH, "evtchw", 0);
		if ((error != 0) && (error != EWOULDBLOCK))
			return (error);
	}

	/* Byte lengths of two chunks. Chunk split (if any) is at ring wrap. */
	if (((c ^ p) & EVTCHN_RING_SIZE) != 0) {
		bytes1 = (EVTCHN_RING_SIZE - EVTCHN_RING_MASK(c)) *
		    sizeof(evtchn_port_t);
		bytes2 = EVTCHN_RING_MASK(p) * sizeof(evtchn_port_t);
	} else {
		bytes1 = (p - c) * sizeof(evtchn_port_t);
		bytes2 = 0;
	}

	/* Truncate chunks according to caller's maximum byte count. */
	if (bytes1 > count) {
		bytes1 = count;
		bytes2 = 0;
	} else if ((bytes1 + bytes2) > count) {
		bytes2 = count - bytes1;
	}

	error = EFAULT;
	rmb(); /* Ensure that we see the port before we copy it. */

	if (uiomove(&u->ring[EVTCHN_RING_MASK(c)], bytes1, uio) ||
	    ((bytes2 != 0) && uiomove(&u->ring[0], bytes2, uio)))
		goto unlock_out;

	u->ring_cons += (bytes1 + bytes2) / sizeof(evtchn_port_t);
	error = 0;

unlock_out:
	sx_xunlock(&u->ring_cons_mutex);
	return (error);
}