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
struct TYPE_2__ {int /*<<< orphan*/  target_id; struct pvscsi_softc* ccb_pvscsi_sc; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct pvscsi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct pvscsi_hcb {int recovery; int /*<<< orphan*/  callout; union ccb* ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PVSCSI_ABORT_TIMEOUT ; 
#define  PVSCSI_HCB_ABORT 131 
#define  PVSCSI_HCB_BUS_RESET 130 
#define  PVSCSI_HCB_DEVICE_RESET 129 
#define  PVSCSI_HCB_NONE 128 
 int PVSCSI_RESET_TIMEOUT ; 
 int SBT_1S ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void (*) (void*),struct pvscsi_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,struct pvscsi_hcb*,union ccb*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_abort (struct pvscsi_softc*,int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  pvscsi_adapter_reset (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_bus_reset (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_device_reset (struct pvscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_freeze (struct pvscsi_softc*) ; 

__attribute__((used)) static void
pvscsi_timeout(void *arg)
{
	struct pvscsi_hcb *hcb;
	struct pvscsi_softc *sc;
	union ccb *ccb;

	hcb = arg;
	ccb = hcb->ccb;

	if (ccb == NULL) {
		/* Already completed */
		return;
	}

	sc = ccb->ccb_h.ccb_pvscsi_sc;
	mtx_assert(&sc->lock, MA_OWNED);

	device_printf(sc->dev, "Command timed out hcb=%p ccb=%p.\n", hcb, ccb);

	switch (hcb->recovery) {
	case PVSCSI_HCB_NONE:
		hcb->recovery = PVSCSI_HCB_ABORT;
		pvscsi_abort(sc, ccb->ccb_h.target_id, ccb);
		callout_reset_sbt(&hcb->callout, PVSCSI_ABORT_TIMEOUT * SBT_1S,
		    0, pvscsi_timeout, hcb, 0);
		break;
	case PVSCSI_HCB_ABORT:
		hcb->recovery = PVSCSI_HCB_DEVICE_RESET;
		pvscsi_freeze(sc);
		pvscsi_device_reset(sc, ccb->ccb_h.target_id);
		callout_reset_sbt(&hcb->callout, PVSCSI_RESET_TIMEOUT * SBT_1S,
		    0, pvscsi_timeout, hcb, 0);
		break;
	case PVSCSI_HCB_DEVICE_RESET:
		hcb->recovery = PVSCSI_HCB_BUS_RESET;
		pvscsi_freeze(sc);
		pvscsi_bus_reset(sc);
		callout_reset_sbt(&hcb->callout, PVSCSI_RESET_TIMEOUT * SBT_1S,
		    0, pvscsi_timeout, hcb, 0);
		break;
	case PVSCSI_HCB_BUS_RESET:
		pvscsi_freeze(sc);
		pvscsi_adapter_reset(sc);
		break;
	};
}