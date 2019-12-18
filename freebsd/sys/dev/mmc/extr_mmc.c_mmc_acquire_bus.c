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
typedef  scalar_t__ uint16_t ;
struct mmc_softc {scalar_t__ last_rca; int child_count; scalar_t__ owner; } ;
struct mmc_ivars {scalar_t__ rca; int /*<<< orphan*/  bus_width; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENXIO ; 
 int MMCBR_ACQUIRE_HOST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MMC_ERR_NONE ; 
 int /*<<< orphan*/  MMC_LOCK (struct mmc_softc*) ; 
 int /*<<< orphan*/  MMC_UNLOCK (struct mmc_softc*) ; 
 scalar_t__ bootverbose ; 
 int bus_timing_mmc_ddr52 ; 
 int bus_timing_mmc_hs200 ; 
 int /*<<< orphan*/  bus_width_4 ; 
 int /*<<< orphan*/  bus_width_8 ; 
 struct mmc_ivars* device_get_ivars (scalar_t__) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 struct mmc_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,scalar_t__,...) ; 
 scalar_t__ mmc_debug ; 
 scalar_t__ mmc_retune (scalar_t__,scalar_t__,int) ; 
 scalar_t__ mmc_select_card (struct mmc_softc*,scalar_t__) ; 
 scalar_t__ mmc_set_card_bus_width (struct mmc_softc*,struct mmc_ivars*,int) ; 
 scalar_t__ mmc_set_vccq (struct mmc_softc*,struct mmc_ivars*,int) ; 
 int /*<<< orphan*/  mmc_timing_to_string (int) ; 
 int mmcbr_get_timing (scalar_t__) ; 
 int /*<<< orphan*/  mmcbr_set_bus_width (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
mmc_acquire_bus(device_t busdev, device_t dev)
{
	struct mmc_softc *sc;
	struct mmc_ivars *ivar;
	int err;
	uint16_t rca;
	enum mmc_bus_timing timing;

	err = MMCBR_ACQUIRE_HOST(device_get_parent(busdev), busdev);
	if (err)
		return (err);
	sc = device_get_softc(busdev);
	MMC_LOCK(sc);
	if (sc->owner)
		panic("mmc: host bridge didn't serialize us.");
	sc->owner = dev;
	MMC_UNLOCK(sc);

	if (busdev != dev) {
		/*
		 * Keep track of the last rca that we've selected.  If
		 * we're asked to do it again, don't.  We never
		 * unselect unless the bus code itself wants the mmc
		 * bus, and constantly reselecting causes problems.
		 */
		ivar = device_get_ivars(dev);
		rca = ivar->rca;
		if (sc->last_rca != rca) {
			if (mmc_select_card(sc, rca) != MMC_ERR_NONE) {
				device_printf(busdev, "Card at relative "
				    "address %d failed to select\n", rca);
				return (ENXIO);
			}
			sc->last_rca = rca;
			timing = mmcbr_get_timing(busdev);
			/*
			 * For eMMC modes, setting/updating bus width and VCCQ
			 * only really is necessary if there actually is more
			 * than one device on the bus as generally that already
			 * had to be done by mmc_calculate_clock() or one of
			 * its calees.  Moreover, setting the bus width anew
			 * can trigger re-tuning (via a CRC error on the next
			 * CMD), even if not switching between devices an the
			 * previously selected one is still tuned.  Obviously,
			 * we need to re-tune the host controller if devices
			 * are actually switched, though.
			 */
			if (timing >= bus_timing_mmc_ddr52 &&
			    sc->child_count == 1)
				return (0);
			/* Prepare bus width for the new card. */
			if (bootverbose || mmc_debug) {
				device_printf(busdev,
				    "setting bus width to %d bits %s timing\n",
				    (ivar->bus_width == bus_width_4) ? 4 :
				    (ivar->bus_width == bus_width_8) ? 8 : 1,
				    mmc_timing_to_string(timing));
			}
			if (mmc_set_card_bus_width(sc, ivar, timing) !=
			    MMC_ERR_NONE) {
				device_printf(busdev, "Card at relative "
				    "address %d failed to set bus width\n",
				    rca);
				return (ENXIO);
			}
			mmcbr_set_bus_width(busdev, ivar->bus_width);
			mmcbr_update_ios(busdev);
			if (mmc_set_vccq(sc, ivar, timing) != MMC_ERR_NONE) {
				device_printf(busdev, "Failed to set VCCQ "
				    "for card at relative address %d\n", rca);
				return (ENXIO);
			}
			if (timing >= bus_timing_mmc_hs200 &&
			    mmc_retune(busdev, dev, true) != 0) {
				device_printf(busdev, "Card at relative "
				    "address %d failed to re-tune\n", rca);
				return (ENXIO);
			}
		}
	} else {
		/*
		 * If there's a card selected, stand down.
		 */
		if (sc->last_rca != 0) {
			if (mmc_select_card(sc, 0) != MMC_ERR_NONE)
				return (ENXIO);
			sc->last_rca = 0;
		}
	}

	return (0);
}