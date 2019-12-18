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
struct puc_cfg {int /*<<< orphan*/  ports; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;

/* Variables and functions */
 int ENXIO ; 
#define  PUC_CFG_GET_OFS 129 
#define  PUC_CFG_GET_RID 128 
 int /*<<< orphan*/  PUC_PORT_2S1P ; 
 int /*<<< orphan*/  PUC_PORT_8S ; 

__attribute__((used)) static int
puc_config_siig(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port,
    intptr_t *res)
{
	const struct puc_cfg *cfg = sc->sc_cfg;

	switch (cmd) {
	case PUC_CFG_GET_OFS:
		if (cfg->ports == PUC_PORT_8S) {
			*res = (port > 4) ? 8 * (port - 4) : 0;
			return (0);
		}
		break;
	case PUC_CFG_GET_RID:
		if (cfg->ports == PUC_PORT_8S) {
			*res = 0x10 + ((port > 4) ? 0x10 : 4 * port);
			return (0);
		}
		if (cfg->ports == PUC_PORT_2S1P) {
			switch (port) {
			case 0: *res = 0x10; return (0);
			case 1: *res = 0x14; return (0);
			case 2: *res = 0x1c; return (0);
			}
		}
		break;
	default:
		break;
	}
	return (ENXIO);
}