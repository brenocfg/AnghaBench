#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct pci_devinfo {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtx; } ;
struct mxge_slice_state {TYPE_1__ tx; } ;
struct TYPE_12__ {int num_slices; int dying; int /*<<< orphan*/  co_hdl; int /*<<< orphan*/  dev; int /*<<< orphan*/  watchdog_resets; struct mxge_slice_state* ss; TYPE_9__* ifp; scalar_t__ link_state; } ;
typedef  TYPE_2__ mxge_softc_t ;
struct TYPE_13__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_close (TYPE_2__*,int) ; 
 int mxge_load_firmware (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int mxge_open (TYPE_2__*) ; 
 int /*<<< orphan*/  mxge_read_reboot (TYPE_2__*) ; 
 int /*<<< orphan*/  mxge_setup_cfg_space (TYPE_2__*) ; 
 int /*<<< orphan*/  mxge_start_locked (struct mxge_slice_state*) ; 
 int /*<<< orphan*/  mxge_tick ; 
 int /*<<< orphan*/  mxge_ticks ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mxge_watchdog_reset(mxge_softc_t *sc)
{
	struct pci_devinfo *dinfo;
	struct mxge_slice_state *ss;
	int err, running, s, num_tx_slices = 1;
	uint32_t reboot;
	uint16_t cmd;

	err = ENXIO;

	device_printf(sc->dev, "Watchdog reset!\n");

	/*
	 * check to see if the NIC rebooted.  If it did, then all of
	 * PCI config space has been reset, and things like the
	 * busmaster bit will be zero.  If this is the case, then we
	 * must restore PCI config space before the NIC can be used
	 * again
	 */
	cmd = pci_read_config(sc->dev, PCIR_COMMAND, 2);
	if (cmd == 0xffff) {
		/*
		 * maybe the watchdog caught the NIC rebooting; wait
		 * up to 100ms for it to finish.  If it does not come
		 * back, then give up
		 */
		DELAY(1000*100);
		cmd = pci_read_config(sc->dev, PCIR_COMMAND, 2);
		if (cmd == 0xffff) {
			device_printf(sc->dev, "NIC disappeared!\n");
		}
	}
	if ((cmd & PCIM_CMD_BUSMASTEREN) == 0) {
		/* print the reboot status */
		reboot = mxge_read_reboot(sc);
		device_printf(sc->dev, "NIC rebooted, status = 0x%x\n",
			      reboot);
		running = sc->ifp->if_drv_flags & IFF_DRV_RUNNING;
		if (running) {

			/*
			 * quiesce NIC so that TX routines will not try to
			 * xmit after restoration of BAR
			 */

			/* Mark the link as down */
			if (sc->link_state) {
				sc->link_state = 0;
				if_link_state_change(sc->ifp,
						     LINK_STATE_DOWN);
			}
#ifdef IFNET_BUF_RING
			num_tx_slices = sc->num_slices;
#endif
			/* grab all TX locks to ensure no tx  */
			for (s = 0; s < num_tx_slices; s++) {
				ss = &sc->ss[s];
				mtx_lock(&ss->tx.mtx);
			}
			mxge_close(sc, 1);
		}
		/* restore PCI configuration space */
		dinfo = device_get_ivars(sc->dev);
		pci_cfg_restore(sc->dev, dinfo);

		/* and redo any changes we made to our config space */
		mxge_setup_cfg_space(sc);

		/* reload f/w */
		err = mxge_load_firmware(sc, 0);
		if (err) {
			device_printf(sc->dev,
				      "Unable to re-load f/w\n");
		}
		if (running) {
			if (!err)
				err = mxge_open(sc);
			/* release all TX locks */
			for (s = 0; s < num_tx_slices; s++) {
				ss = &sc->ss[s];
#ifdef IFNET_BUF_RING
				mxge_start_locked(ss);
#endif
				mtx_unlock(&ss->tx.mtx);
			}
		}
		sc->watchdog_resets++;
	} else {
		device_printf(sc->dev,
			      "NIC did not reboot, not resetting\n");
		err = 0;
	}
	if (err) {
		device_printf(sc->dev, "watchdog reset failed\n");
	} else {
		if (sc->dying == 2)
			sc->dying = 0;
		callout_reset(&sc->co_hdl, mxge_ticks, mxge_tick, sc);
	}
}