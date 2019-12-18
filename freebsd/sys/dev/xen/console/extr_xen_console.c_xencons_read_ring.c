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
struct xencons_priv {struct xencons_interface* intf; } ;
struct xencons_interface {scalar_t__ in_cons; scalar_t__ in_prod; char* in; } ;
typedef  scalar_t__ XENCONS_RING_IDX ;

/* Variables and functions */
 size_t MASK_XENCONS_IDX (scalar_t__,char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xencons_lock_assert (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_notify_ring (struct xencons_priv*) ; 

__attribute__((used)) static int
xencons_read_ring(struct xencons_priv *cons, char *buffer, unsigned int size)
{
	struct xencons_interface *intf;
	XENCONS_RING_IDX rcons, rprod;
	unsigned int rsz;

	intf = cons->intf;

	xencons_lock_assert(cons);

	rcons = intf->in_cons;
	rprod = intf->in_prod;
	rmb();

	for (rsz = 0; rsz < size; rsz++, rcons++) {
		if (rprod == rcons)
			break;
		buffer[rsz] = intf->in[MASK_XENCONS_IDX(rcons, intf->in)];
	}

	wmb();
	intf->in_cons = rcons;

	/* No need to notify the backend if nothing has been read */
	if (rsz != 0)
		xencons_notify_ring(cons);

	return (rsz);
}