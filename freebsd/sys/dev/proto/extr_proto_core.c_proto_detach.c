#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct proto_softc {int sc_opencnt; scalar_t__ sc_rescnt; int /*<<< orphan*/  sc_mtx; struct proto_res* sc_res; } ;
struct TYPE_4__ {int /*<<< orphan*/  busdma; int /*<<< orphan*/  res; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdev; } ;
struct proto_res {int r_type; TYPE_2__ r_d; TYPE_1__ r_u; int /*<<< orphan*/  r_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
#define  PROTO_RES_BUSDMA 133 
#define  PROTO_RES_PCICFG 132 
 int PROTO_RES_UNUSED ; 
#define  SYS_RES_DRQ 131 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct proto_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_busdma_detach (struct proto_softc*,int /*<<< orphan*/ ) ; 

int
proto_detach(device_t dev)
{
	struct proto_softc *sc;
	struct proto_res *r;
	u_int res;

	sc = device_get_softc(dev);

	mtx_lock(&sc->sc_mtx);
	if (sc->sc_opencnt == 0)
		sc->sc_opencnt = -1;
	mtx_unlock(&sc->sc_mtx);
	if (sc->sc_opencnt > 0)
		return (EBUSY);

	for (res = 0; res < sc->sc_rescnt; res++) {
		r = sc->sc_res + res;

		switch (r->r_type) {
		case SYS_RES_IRQ:
			/* XXX TODO */
			bus_release_resource(dev, r->r_type, r->r_rid,
			    r->r_d.res);
			break;
		case SYS_RES_DRQ:
			bus_release_resource(dev, r->r_type, r->r_rid,
			    r->r_d.res);
			break;
		case SYS_RES_MEMORY:
		case SYS_RES_IOPORT:
			destroy_dev(r->r_u.cdev);
			bus_release_resource(dev, r->r_type, r->r_rid,
			    r->r_d.res);
			break;
		case PROTO_RES_PCICFG:
			destroy_dev(r->r_u.cdev);
			break;
		case PROTO_RES_BUSDMA:
			destroy_dev(r->r_u.cdev);
			proto_busdma_detach(sc, r->r_d.busdma);
			break;
		}
		r->r_type = PROTO_RES_UNUSED;
	}
	mtx_lock(&sc->sc_mtx);
	sc->sc_rescnt = 0;
	sc->sc_opencnt = 0;
	mtx_unlock(&sc->sc_mtx);
	mtx_destroy(&sc->sc_mtx);
	return (0);
}