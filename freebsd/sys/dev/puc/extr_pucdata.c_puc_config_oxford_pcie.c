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
typedef  int uint8_t ;
struct puc_softc {int sc_nports; int sc_cfg_data; TYPE_1__* sc_bar; int /*<<< orphan*/  sc_dev; struct puc_cfg* sc_cfg; } ;
struct puc_cfg {int /*<<< orphan*/  rid; } ;
struct puc_bar {int /*<<< orphan*/  b_res; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;
struct TYPE_2__ {int b_rid; } ;

/* Variables and functions */
 int ENXIO ; 
#define  PUC_CFG_GET_LEN 132 
#define  PUC_CFG_GET_NPORTS 131 
#define  PUC_CFG_GET_OFS 130 
#define  PUC_CFG_GET_TYPE 129 
#define  PUC_CFG_SETUP 128 
 int PUC_PCI_BARS ; 
 intptr_t PUC_TYPE_SERIAL ; 
 int bus_read_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct puc_bar* puc_get_bar (struct puc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
puc_config_oxford_pcie(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port,
    intptr_t *res)
{
	const struct puc_cfg *cfg = sc->sc_cfg;
	int idx;
	struct puc_bar *bar;
	uint8_t value;

	switch (cmd) {
	case PUC_CFG_SETUP:
		device_printf(sc->sc_dev, "%d UARTs detected\n",
			sc->sc_nports);

		/* Set UARTs to enhanced mode */
		bar = puc_get_bar(sc, cfg->rid);
		if (bar == NULL)
			return (ENXIO);
		for (idx = 0; idx < sc->sc_nports; idx++) {
			value = bus_read_1(bar->b_res, 0x1000 + (idx << 9) +
			    0x92);
			bus_write_1(bar->b_res, 0x1000 + (idx << 9) + 0x92,
			    value | 0x10);
		}
		return (0);
	case PUC_CFG_GET_LEN:
		*res = 0x200;
		return (0);
	case PUC_CFG_GET_NPORTS:
		/*
		 * Check if we are being called from puc_bfe_attach()
		 * or puc_bfe_probe().  If puc_bfe_probe(), we cannot
		 * puc_get_bar(), so we return a value of 16.  This has
		 * cosmetic side-effects at worst; in PUC_CFG_GET_DESC,
		 * sc->sc_cfg_data will not contain the true number of
		 * ports in PUC_CFG_GET_DESC, but we are not implementing
		 * that call for this device family anyway.
		 *
		 * The check is for initialization of sc->sc_bar[idx],
		 * which is only done in puc_bfe_attach().
		 */
		idx = 0;
		do {
			if (sc->sc_bar[idx++].b_rid != -1) {
				sc->sc_cfg_data = 16;
				*res = sc->sc_cfg_data;
				return (0);
			}
		} while (idx < PUC_PCI_BARS);

		bar = puc_get_bar(sc, cfg->rid);
		if (bar == NULL)
			return (ENXIO);

		value = bus_read_1(bar->b_res, 0x04);
		if (value == 0)
			return (ENXIO);

		sc->sc_cfg_data = value;
		*res = sc->sc_cfg_data;
		return (0);
	case PUC_CFG_GET_OFS:
		*res = 0x1000 + (port << 9);
		return (0);
	case PUC_CFG_GET_TYPE:
		*res = PUC_TYPE_SERIAL;
		return (0);
	default:
		break;
	}
	return (ENXIO);
}