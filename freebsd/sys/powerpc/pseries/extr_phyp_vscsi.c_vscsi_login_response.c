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
typedef  int /*<<< orphan*/  uint8_t ;
struct vscsi_xfer {scalar_t__ srp_iu_offset; struct vscsi_softc* sc; } ;
struct vscsi_softc {int bus_logged_in; int /*<<< orphan*/  max_transactions; int /*<<< orphan*/  dev; scalar_t__ srp_iu_queue; } ;
struct vscsi_crq {int dummy; } ;
struct srp_login_rsp {int /*<<< orphan*/  request_limit_delta; int /*<<< orphan*/  buffer_formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vscsi_login_response(struct vscsi_xfer *xp, struct vscsi_crq *crq)
{
	struct vscsi_softc *sc = xp->sc;
	struct srp_login_rsp *rsp;

	/* SRP response packet in original request */
	rsp = (struct srp_login_rsp *)((uint8_t *)sc->srp_iu_queue +
	    (uintptr_t)xp->srp_iu_offset);
	KASSERT(be16toh(rsp->buffer_formats) & 0x3, ("Both direct and indirect "
	    "buffers supported"));

	sc->max_transactions = be32toh(rsp->request_limit_delta);
	device_printf(sc->dev, "Queue depth %d commands\n",
	    sc->max_transactions);
	sc->bus_logged_in = 1;
}