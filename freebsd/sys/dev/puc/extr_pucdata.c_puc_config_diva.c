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
struct puc_softc {struct puc_cfg* sc_cfg; } ;
struct puc_cfg {int subdevice; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;

/* Variables and functions */
 int ENXIO ; 
 int PUC_CFG_GET_OFS ; 

__attribute__((used)) static int
puc_config_diva(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port,
    intptr_t *res)
{
	const struct puc_cfg *cfg = sc->sc_cfg;

	if (cmd == PUC_CFG_GET_OFS) {
		if (cfg->subdevice == 0x1282)		/* Everest SP */
			port <<= 1;
		else if (cfg->subdevice == 0x104b)	/* Maestro SP2 */
			port = (port == 3) ? 4 : port;
		*res = port * 8 + ((port > 2) ? 0x18 : 0);
		return (0);
	}
	return (ENXIO);
}