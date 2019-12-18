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
struct puc_softc {struct puc_cfg const* sc_cfg; int /*<<< orphan*/  sc_dev; } ;
struct puc_cfg {scalar_t__ ports; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  PUC_CFG_GET_DESC ; 
 int /*<<< orphan*/  PUC_CFG_GET_NPORTS ; 
 scalar_t__ PUC_PORT_1P ; 
 scalar_t__ PUC_PORT_1S ; 
 struct puc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int puc_config (struct puc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t*) ; 

int
puc_bfe_probe(device_t dev, const struct puc_cfg *cfg)
{
	struct puc_softc *sc;
	intptr_t res;
	int error;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_cfg = cfg;

	/* We don't attach to single-port serial cards. */
	if (cfg->ports == PUC_PORT_1S || cfg->ports == PUC_PORT_1P)
		return (EDOOFUS);
	error = puc_config(sc, PUC_CFG_GET_NPORTS, 0, &res);
	if (error)
		return (error);
	error = puc_config(sc, PUC_CFG_GET_DESC, 0, &res);
	if (error)
		return (error);
	if (res != 0)
		device_set_desc(dev, (const char *)res);
	return (BUS_PROBE_DEFAULT);
}