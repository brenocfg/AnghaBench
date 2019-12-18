#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct hifn_softc {int /*<<< orphan*/  sc_dev; } ;
struct TYPE_3__ {scalar_t__ pci_vendor; scalar_t__ pci_prod; char* card_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HIFN_0_PUCNFG ; 
 int /*<<< orphan*/  HIFN_0_PUSTAT ; 
 int /*<<< orphan*/  HIFN_1_DMA_CNFG ; 
 size_t HIFN_DMACNFG_DMARESET ; 
 size_t HIFN_DMACNFG_MODE ; 
 size_t HIFN_DMACNFG_MSTRESET ; 
 size_t HIFN_DMACNFG_UNLOCK ; 
 size_t HIFN_PUCNFG_CHIPID ; 
 size_t HIFN_PUSTAT_CHIPENA ; 
#define  HIFN_PUSTAT_ENA_0 130 
#define  HIFN_PUSTAT_ENA_1 129 
#define  HIFN_PUSTAT_ENA_2 128 
 int /*<<< orphan*/  HIFN_UNLOCK_SECRET1 ; 
 int /*<<< orphan*/  HIFN_UNLOCK_SECRET2 ; 
 size_t READ_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 size_t READ_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WRITE_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hifn_debug ; 
 size_t hifn_next_signature (size_t,char) ; 
 size_t nitems (TYPE_1__*) ; 
 TYPE_1__* pci2id ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
hifn_enable_crypto(struct hifn_softc *sc)
{
	u_int32_t dmacfg, ramcfg, encl, addr, i;
	char *offtbl = NULL;

	for (i = 0; i < nitems(pci2id); i++) {
		if (pci2id[i].pci_vendor == pci_get_vendor(sc->sc_dev) &&
		    pci2id[i].pci_prod == pci_get_device(sc->sc_dev)) {
			offtbl = pci2id[i].card_id;
			break;
		}
	}
	if (offtbl == NULL) {
		device_printf(sc->sc_dev, "Unknown card!\n");
		return (1);
	}

	ramcfg = READ_REG_0(sc, HIFN_0_PUCNFG);
	dmacfg = READ_REG_1(sc, HIFN_1_DMA_CNFG);

	/*
	 * The RAM config register's encrypt level bit needs to be set before
	 * every read performed on the encryption level register.
	 */
	WRITE_REG_0(sc, HIFN_0_PUCNFG, ramcfg | HIFN_PUCNFG_CHIPID);

	encl = READ_REG_0(sc, HIFN_0_PUSTAT) & HIFN_PUSTAT_CHIPENA;

	/*
	 * Make sure we don't re-unlock.  Two unlocks kills chip until the
	 * next reboot.
	 */
	if (encl == HIFN_PUSTAT_ENA_1 || encl == HIFN_PUSTAT_ENA_2) {
#ifdef HIFN_DEBUG
		if (hifn_debug)
			device_printf(sc->sc_dev,
			    "Strong crypto already enabled!\n");
#endif
		goto report;
	}

	if (encl != 0 && encl != HIFN_PUSTAT_ENA_0) {
#ifdef HIFN_DEBUG
		if (hifn_debug)
			device_printf(sc->sc_dev,
			      "Unknown encryption level 0x%x\n", encl);
#endif
		return 1;
	}

	WRITE_REG_1(sc, HIFN_1_DMA_CNFG, HIFN_DMACNFG_UNLOCK |
	    HIFN_DMACNFG_MSTRESET | HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);
	DELAY(1000);
	addr = READ_REG_1(sc, HIFN_UNLOCK_SECRET1);
	DELAY(1000);
	WRITE_REG_1(sc, HIFN_UNLOCK_SECRET2, 0);
	DELAY(1000);

	for (i = 0; i <= 12; i++) {
		addr = hifn_next_signature(addr, offtbl[i] + 0x101);
		WRITE_REG_1(sc, HIFN_UNLOCK_SECRET2, addr);

		DELAY(1000);
	}

	WRITE_REG_0(sc, HIFN_0_PUCNFG, ramcfg | HIFN_PUCNFG_CHIPID);
	encl = READ_REG_0(sc, HIFN_0_PUSTAT) & HIFN_PUSTAT_CHIPENA;

#ifdef HIFN_DEBUG
	if (hifn_debug) {
		if (encl != HIFN_PUSTAT_ENA_1 && encl != HIFN_PUSTAT_ENA_2)
			device_printf(sc->sc_dev, "Engine is permanently "
				"locked until next system reset!\n");
		else
			device_printf(sc->sc_dev, "Engine enabled "
				"successfully!\n");
	}
#endif

report:
	WRITE_REG_0(sc, HIFN_0_PUCNFG, ramcfg);
	WRITE_REG_1(sc, HIFN_1_DMA_CNFG, dmacfg);

	switch (encl) {
	case HIFN_PUSTAT_ENA_1:
	case HIFN_PUSTAT_ENA_2:
		break;
	case HIFN_PUSTAT_ENA_0:
	default:
		device_printf(sc->sc_dev, "disabled");
		break;
	}

	return 0;
}