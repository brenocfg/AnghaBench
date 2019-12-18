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
struct port_info {int flags; int /*<<< orphan*/  media; int /*<<< orphan*/  tick; int /*<<< orphan*/ * vi; struct adapter* adapter; } ;
struct adapter {int traceq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HAS_TRACEQ ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbe_vi_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct port_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doom_vi (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tracer_port_detach (struct adapter*) ; 

__attribute__((used)) static int
cxgbe_detach(device_t dev)
{
	struct port_info *pi = device_get_softc(dev);
	struct adapter *sc = pi->adapter;
	int rc;

	/* Detach the extra VIs first. */
	rc = bus_generic_detach(dev);
	if (rc)
		return (rc);
	device_delete_children(dev);

	doom_vi(sc, &pi->vi[0]);

	if (pi->flags & HAS_TRACEQ) {
		sc->traceq = -1;	/* cloner should not create ifnet */
		t4_tracer_port_detach(sc);
	}

	cxgbe_vi_detach(&pi->vi[0]);
	callout_drain(&pi->tick);
	ifmedia_removeall(&pi->media);

	end_synchronized_op(sc, 0);

	return (0);
}