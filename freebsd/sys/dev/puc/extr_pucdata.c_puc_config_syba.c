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
typedef  int uint8_t ;
struct puc_softc {struct puc_cfg* sc_cfg; } ;
struct puc_cfg {int /*<<< orphan*/  rid; } ;
struct puc_bar {int /*<<< orphan*/  b_res; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;

/* Variables and functions */
 int ENXIO ; 
#define  PUC_CFG_GET_OFS 129 
#define  PUC_CFG_SETUP 128 
 int bus_read_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int) ; 
 struct puc_bar* puc_get_bar (struct puc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
puc_config_syba(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port,
    intptr_t *res)
{
	static int base[] = { 0x251, 0x3f0, 0 };
	const struct puc_cfg *cfg = sc->sc_cfg;
	struct puc_bar *bar;
	int efir, idx, ofs;
	uint8_t v;

	switch (cmd) {
	case PUC_CFG_SETUP:
		bar = puc_get_bar(sc, cfg->rid);
		if (bar == NULL)
			return (ENXIO);

		/* configure both W83877TFs */
		bus_write_1(bar->b_res, 0x250, 0x89);
		bus_write_1(bar->b_res, 0x3f0, 0x87);
		bus_write_1(bar->b_res, 0x3f0, 0x87);
		idx = 0;
		while (base[idx] != 0) {
			efir = base[idx];
			bus_write_1(bar->b_res, efir, 0x09);
			v = bus_read_1(bar->b_res, efir + 1);
			if ((v & 0x0f) != 0x0c)
				return (ENXIO);
			bus_write_1(bar->b_res, efir, 0x16);
			v = bus_read_1(bar->b_res, efir + 1);
			bus_write_1(bar->b_res, efir, 0x16);
			bus_write_1(bar->b_res, efir + 1, v | 0x04);
			bus_write_1(bar->b_res, efir, 0x16);
			bus_write_1(bar->b_res, efir + 1, v & ~0x04);
			ofs = base[idx] & 0x300;
			bus_write_1(bar->b_res, efir, 0x23);
			bus_write_1(bar->b_res, efir + 1, (ofs + 0x78) >> 2);
			bus_write_1(bar->b_res, efir, 0x24);
			bus_write_1(bar->b_res, efir + 1, (ofs + 0xf8) >> 2);
			bus_write_1(bar->b_res, efir, 0x25);
			bus_write_1(bar->b_res, efir + 1, (ofs + 0xe8) >> 2);
			bus_write_1(bar->b_res, efir, 0x17);
			bus_write_1(bar->b_res, efir + 1, 0x03);
			bus_write_1(bar->b_res, efir, 0x28);
			bus_write_1(bar->b_res, efir + 1, 0x43);
			idx++;
		}
		bus_write_1(bar->b_res, 0x250, 0xaa);
		bus_write_1(bar->b_res, 0x3f0, 0xaa);
		return (0);
	case PUC_CFG_GET_OFS:
		switch (port) {
		case 0:
			*res = 0x2f8;
			return (0);
		case 1:
			*res = 0x2e8;
			return (0);
		case 2:
			*res = 0x3f8;
			return (0);
		case 3:
			*res = 0x3e8;
			return (0);
		case 4:
			*res = 0x278;
			return (0);
		}
		break;
	default:
		break;
	}
	return (ENXIO);
}