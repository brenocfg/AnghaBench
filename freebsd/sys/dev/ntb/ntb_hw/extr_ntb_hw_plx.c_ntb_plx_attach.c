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
typedef  int uint32_t ;
struct ntb_plx_softc {int ntx; int link; int conf_rid; int port; int alut; size_t mw_count; int b2b_mw; int b2b_off; int split; int spad_offp2; int spad_off2; int spad_count1; int spad_count2; int /*<<< orphan*/ * conf_res; scalar_t__ spad_offp1; scalar_t__ spad_off1; struct ntb_plx_mw_info* mw_info; int /*<<< orphan*/  dev; } ;
struct ntb_plx_mw_info {int mw_bar; int mw_rid; int mw_size; int mw_64bit; TYPE_1__* splits; int /*<<< orphan*/ * mw_res; int /*<<< orphan*/  mw_vbase; int /*<<< orphan*/  mw_pbase; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  mw_map_mode; } ;

/* Variables and functions */
 int ENXIO ; 
 int PCIM_BAR_MEM_64 ; 
 int PCIM_BAR_MEM_TYPE ; 
 int PCIR_BAR (int) ; 
 int PLX_MAX_SPLIT ; 
 scalar_t__ PLX_NTX_OUR_BASE (struct ntb_plx_softc*) ; 
 int PLX_NUM_SPAD ; 
 int PLX_NUM_SPAD_PATT ; 
 int PLX_PORT_BASE (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_read_4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int,int) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ntb_plx_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_plx_init (int /*<<< orphan*/ ) ; 
 int ntb_plx_setup_intr (int /*<<< orphan*/ ) ; 
 int ntb_register_device (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_virtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
ntb_plx_attach(device_t dev)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;
	int error = 0, i, j;
	uint32_t val;
	char buf[32];

	/* Identify what we are (what side of what NTx). */
	sc->dev = dev;
	val = pci_read_config(dev, 0xc8c, 4);
	sc->ntx = (val & 1) != 0;
	sc->link = (val & 0x80000000) != 0;

	/* Get access to whole 256KB of chip configuration space via BAR0/1. */
	sc->conf_rid = PCIR_BAR(0);
	sc->conf_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->conf_rid, RF_ACTIVE);
	if (sc->conf_res == NULL) {
		device_printf(dev, "Can't allocate configuration BAR.\n");
		return (ENXIO);
	}

	/* Identify chip port we are connected to. */
	val = bus_read_4(sc->conf_res, 0x360);
	sc->port = (val >> ((sc->ntx == 0) ? 8 : 16)) & 0x1f;

	/* Detect A-LUT enable and size. */
	val >>= 30;
	sc->alut = (val == 0x3) ? 1 : ((val & (1 << sc->ntx)) ? 2 : 0);
	if (sc->alut)
		device_printf(dev, "%u A-LUT entries\n", 128 * sc->alut);

	/* Find configured memory windows at BAR2-5. */
	sc->mw_count = 0;
	for (i = 2; i <= 5; i++) {
		mw = &sc->mw_info[sc->mw_count];
		mw->mw_bar = i;
		mw->mw_rid = PCIR_BAR(mw->mw_bar);
		mw->mw_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		    &mw->mw_rid, RF_ACTIVE);
		if (mw->mw_res == NULL)
			continue;
		mw->mw_pbase = rman_get_start(mw->mw_res);
		mw->mw_size = rman_get_size(mw->mw_res);
		mw->mw_vbase = rman_get_virtual(mw->mw_res);
		for (j = 0; j < PLX_MAX_SPLIT; j++)
			mw->splits[j].mw_map_mode = VM_MEMATTR_UNCACHEABLE;
		sc->mw_count++;

		/* Skip over adjacent BAR for 64-bit BARs. */
		val = pci_read_config(dev, PCIR_BAR(mw->mw_bar), 4);
		if ((val & PCIM_BAR_MEM_TYPE) == PCIM_BAR_MEM_64) {
			mw->mw_64bit = 1;
			i++;
		}
	}

	/* Try to identify B2B mode. */
	i = 1;
	snprintf(buf, sizeof(buf), "hint.%s.%d.b2b", device_get_name(dev),
	    device_get_unit(dev));
	TUNABLE_INT_FETCH(buf, &i);
	if (sc->link) {
		device_printf(dev, "NTB-to-Root Port mode (Link Interface)\n");
		sc->b2b_mw = -1;
	} else if (i == 0) {
		device_printf(dev, "NTB-to-Root Port mode (Virtual Interface)\n");
		sc->b2b_mw = -1;
	} else {
		device_printf(dev, "NTB-to-NTB (back-to-back) mode\n");

		/* We need at least one memory window for B2B peer access. */
		if (sc->mw_count == 0) {
			device_printf(dev, "No memory window BARs enabled.\n");
			error = ENXIO;
			goto out;
		}
		sc->b2b_mw = sc->mw_count - 1;

		/* Use half of the window for B2B, but no less then 1MB. */
		mw = &sc->mw_info[sc->b2b_mw];
		if (mw->mw_size >= 2 * 1024 * 1024)
			sc->b2b_off = mw->mw_size / 2;
		else
			sc->b2b_off = 0;
	}

	snprintf(buf, sizeof(buf), "hint.%s.%d.split", device_get_name(dev),
	    device_get_unit(dev));
	TUNABLE_INT_FETCH(buf, &sc->split);
	if (sc->split > 7) {
		device_printf(dev, "Split value is too high (%u)\n", sc->split);
		sc->split = 0;
	} else if (sc->split > 0 && sc->alut == 0) {
		device_printf(dev, "Can't split with disabled A-LUT\n");
		sc->split = 0;
	} else if (sc->split > 0 && (sc->mw_count == 0 || sc->mw_info[0].mw_bar != 2)) {
		device_printf(dev, "Can't split disabled BAR2\n");
		sc->split = 0;
	} else if (sc->split > 0 && (sc->b2b_mw == 0 && sc->b2b_off == 0)) {
		device_printf(dev, "Can't split BAR2 consumed by B2B\n");
		sc->split = 0;
	} else if (sc->split > 0) {
		device_printf(dev, "Splitting BAR2 into %d memory windows\n",
		    1 << sc->split);
	}

	/*
	 * Use Physical Layer User Test Pattern as additional scratchpad.
	 * Make sure they are present and enabled by writing to them.
	 * XXX: Its a hack, but standard 8 registers are not enough.
	 */
	sc->spad_offp1 = sc->spad_off1 = PLX_NTX_OUR_BASE(sc) + 0xc6c;
	sc->spad_offp2 = sc->spad_off2 = PLX_PORT_BASE(sc->ntx * 8) + 0x20c;
	if (sc->b2b_mw >= 0) {
		/* In NTB-to-NTB mode each side has own scratchpads. */
		sc->spad_count1 = PLX_NUM_SPAD;
		bus_write_4(sc->conf_res, sc->spad_off2, 0x12345678);
		if (bus_read_4(sc->conf_res, sc->spad_off2) == 0x12345678)
			sc->spad_count2 = PLX_NUM_SPAD_PATT;
	} else {
		/* Otherwise we have share scratchpads with the peer. */
		if (sc->link) {
			sc->spad_off1 += PLX_NUM_SPAD / 2 * 4;
			sc->spad_off2 += PLX_NUM_SPAD_PATT / 2 * 4;
		} else {
			sc->spad_offp1 += PLX_NUM_SPAD / 2 * 4;
			sc->spad_offp2 += PLX_NUM_SPAD_PATT / 2 * 4;
		}
		sc->spad_count1 = PLX_NUM_SPAD / 2;
		bus_write_4(sc->conf_res, sc->spad_off2, 0x12345678);
		if (bus_read_4(sc->conf_res, sc->spad_off2) == 0x12345678)
			sc->spad_count2 = PLX_NUM_SPAD_PATT / 2;
	}

	/* Apply static part of NTB configuration. */
	ntb_plx_init(dev);

	/* Allocate and setup interrupts. */
	error = ntb_plx_setup_intr(dev);
	if (error)
		goto out;

	/* Attach children to this controller */
	error = ntb_register_device(dev);

out:
	if (error != 0)
		ntb_plx_detach(dev);
	return (error);
}