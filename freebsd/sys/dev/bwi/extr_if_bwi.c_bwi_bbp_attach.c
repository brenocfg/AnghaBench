#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bwi_softc {scalar_t__ sc_pci_did; scalar_t__ sc_nmac; TYPE_1__* sc_mac; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bus_regwin; int /*<<< orphan*/  sc_com_regwin; void* sc_cap; void* sc_bbp_pkg; void* sc_bbp_rev; scalar_t__ sc_bbp_id; int /*<<< orphan*/  sc_pci_revid; } ;
struct TYPE_6__ {scalar_t__ did_min; scalar_t__ did_max; scalar_t__ bbp_id; int nregwin; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac_regwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_CAPABILITY ; 
 int /*<<< orphan*/  BWI_CREATE_REGWIN (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 int /*<<< orphan*/  BWI_DBG_ATTACH ; 
 int /*<<< orphan*/  BWI_INFO ; 
 int /*<<< orphan*/  BWI_INFO_BBPID_MASK ; 
 int /*<<< orphan*/  BWI_INFO_BBPPKG_MASK ; 
 int /*<<< orphan*/  BWI_INFO_BBPREV_MASK ; 
 int /*<<< orphan*/  BWI_INFO_NREGWIN_MASK ; 
 scalar_t__ BWI_REGWIN_EXIST (int /*<<< orphan*/ *) ; 
 scalar_t__ BWI_REGWIN_T_BUSPCI ; 
 scalar_t__ BWI_REGWIN_T_BUSPCIE ; 
 scalar_t__ BWI_REGWIN_T_COM ; 
 scalar_t__ BWI_REGWIN_T_MAC ; 
 void* CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int /*<<< orphan*/ ,char*,int,void*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int __SHIFTIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* bwi_bbpid_map ; 
 int /*<<< orphan*/  bwi_mac_attach (struct bwi_softc*,int,int) ; 
 TYPE_2__* bwi_regwin_count ; 
 int /*<<< orphan*/  bwi_regwin_info (struct bwi_softc*,scalar_t__*,int*) ; 
 int bwi_regwin_select (struct bwi_softc*,int) ; 
 int bwi_regwin_switch (struct bwi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (TYPE_2__*) ; 

__attribute__((used)) static int
bwi_bbp_attach(struct bwi_softc *sc)
{
	uint16_t bbp_id, rw_type;
	uint8_t rw_rev;
	uint32_t info;
	int error, nregwin, i;

	/*
	 * Get 0th regwin information
	 * NOTE: 0th regwin should exist
	 */
	error = bwi_regwin_select(sc, 0);
	if (error) {
		device_printf(sc->sc_dev, "can't select regwin 0\n");
		return error;
	}
	bwi_regwin_info(sc, &rw_type, &rw_rev);

	/*
	 * Find out BBP id
	 */
	bbp_id = 0;
	info = 0;
	if (rw_type == BWI_REGWIN_T_COM) {
		info = CSR_READ_4(sc, BWI_INFO);
		bbp_id = __SHIFTOUT(info, BWI_INFO_BBPID_MASK);

		BWI_CREATE_REGWIN(&sc->sc_com_regwin, 0, rw_type, rw_rev);

		sc->sc_cap = CSR_READ_4(sc, BWI_CAPABILITY);
	} else {
		for (i = 0; i < nitems(bwi_bbpid_map); ++i) {
			if (sc->sc_pci_did >= bwi_bbpid_map[i].did_min &&
			    sc->sc_pci_did <= bwi_bbpid_map[i].did_max) {
				bbp_id = bwi_bbpid_map[i].bbp_id;
				break;
			}
		}
		if (bbp_id == 0) {
			device_printf(sc->sc_dev, "no BBP id for device id "
				      "0x%04x\n", sc->sc_pci_did);
			return ENXIO;
		}

		info = __SHIFTIN(sc->sc_pci_revid, BWI_INFO_BBPREV_MASK) |
		       __SHIFTIN(0, BWI_INFO_BBPPKG_MASK);
	}

	/*
	 * Find out number of regwins
	 */
	nregwin = 0;
	if (rw_type == BWI_REGWIN_T_COM && rw_rev >= 4) {
		nregwin = __SHIFTOUT(info, BWI_INFO_NREGWIN_MASK);
	} else {
		for (i = 0; i < nitems(bwi_regwin_count); ++i) {
			if (bwi_regwin_count[i].bbp_id == bbp_id) {
				nregwin = bwi_regwin_count[i].nregwin;
				break;
			}
		}
		if (nregwin == 0) {
			device_printf(sc->sc_dev, "no number of win for "
				      "BBP id 0x%04x\n", bbp_id);
			return ENXIO;
		}
	}

	/* Record BBP id/rev for later using */
	sc->sc_bbp_id = bbp_id;
	sc->sc_bbp_rev = __SHIFTOUT(info, BWI_INFO_BBPREV_MASK);
	sc->sc_bbp_pkg = __SHIFTOUT(info, BWI_INFO_BBPPKG_MASK);
	device_printf(sc->sc_dev, "BBP: id 0x%04x, rev 0x%x, pkg %d\n",
		      sc->sc_bbp_id, sc->sc_bbp_rev, sc->sc_bbp_pkg);

	DPRINTF(sc, BWI_DBG_ATTACH, "nregwin %d, cap 0x%08x\n",
		nregwin, sc->sc_cap);

	/*
	 * Create rest of the regwins
	 */

	/* Don't re-create common regwin, if it is already created */
	i = BWI_REGWIN_EXIST(&sc->sc_com_regwin) ? 1 : 0;

	for (; i < nregwin; ++i) {
		/*
		 * Get regwin information
		 */
		error = bwi_regwin_select(sc, i);
		if (error) {
			device_printf(sc->sc_dev,
				      "can't select regwin %d\n", i);
			return error;
		}
		bwi_regwin_info(sc, &rw_type, &rw_rev);

		/*
		 * Try attach:
		 * 1) Bus (PCI/PCIE) regwin
		 * 2) MAC regwin
		 * Ignore rest types of regwin
		 */
		if (rw_type == BWI_REGWIN_T_BUSPCI ||
		    rw_type == BWI_REGWIN_T_BUSPCIE) {
			if (BWI_REGWIN_EXIST(&sc->sc_bus_regwin)) {
				device_printf(sc->sc_dev,
					      "bus regwin already exists\n");
			} else {
				BWI_CREATE_REGWIN(&sc->sc_bus_regwin, i,
						  rw_type, rw_rev);
			}
		} else if (rw_type == BWI_REGWIN_T_MAC) {
			/* XXX ignore return value */
			bwi_mac_attach(sc, i, rw_rev);
		}
	}

	/* At least one MAC shold exist */
	if (!BWI_REGWIN_EXIST(&sc->sc_mac[0].mac_regwin)) {
		device_printf(sc->sc_dev, "no MAC was found\n");
		return ENXIO;
	}
	KASSERT(sc->sc_nmac > 0, ("no mac's"));

	/* Bus regwin must exist */
	if (!BWI_REGWIN_EXIST(&sc->sc_bus_regwin)) {
		device_printf(sc->sc_dev, "no bus regwin was found\n");
		return ENXIO;
	}

	/* Start with first MAC */
	error = bwi_regwin_switch(sc, &sc->sc_mac[0].mac_regwin, NULL);
	if (error)
		return error;

	return 0;
}