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
struct xencons_interface {int out_cons; int out_prod; char* out; } ;
typedef  int XENCONS_RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MASK_XENCONS_IDX (int,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xencons_lock_assert (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_notify_ring (struct xencons_priv*) ; 

__attribute__((used)) static int
xencons_write_ring(struct xencons_priv *cons, const char *buffer,
    unsigned int size)
{
	struct xencons_interface *intf;
	XENCONS_RING_IDX wcons, wprod;
	int sent;

	intf = cons->intf;

	xencons_lock_assert(cons);

	wcons = intf->out_cons;
	wprod = intf->out_prod;

	mb();
	KASSERT((wprod - wcons) <= sizeof(intf->out),
		("console send ring inconsistent"));

	for (sent = 0; sent < size; sent++, wprod++) {
		if ((wprod - wcons) >= sizeof(intf->out))
			break;
		intf->out[MASK_XENCONS_IDX(wprod, intf->out)] = buffer[sent];
	}

	wmb();
	intf->out_prod = wprod;

	xencons_notify_ring(cons);

	return (sent);
}