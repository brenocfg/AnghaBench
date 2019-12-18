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
typedef  int uint32_t ;
struct pincfg {int padconf_val; int mux_reg; int mux_val; int input_reg; int input_val; int padconf_reg; } ;
struct iomux_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,char**,int) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (struct pincfg*) ; 
 int PADCONF_NONE ; 
 int PADCONF_SION ; 
 int PADMUX_SION ; 
 int /*<<< orphan*/  WR4 (struct iomux_softc*,int,int) ; 
 scalar_t__ bootverbose ; 
 struct iomux_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomux_configure_input (struct iomux_softc*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
iomux_configure_pins(device_t dev, phandle_t cfgxref)
{
	struct iomux_softc *sc;
	struct pincfg *cfgtuples, *cfg;
	phandle_t cfgnode;
	int i, ntuples;
	uint32_t sion;

	sc = device_get_softc(dev);
	cfgnode = OF_node_from_xref(cfgxref);
	ntuples = OF_getencprop_alloc_multi(cfgnode, "fsl,pins",
	    sizeof(*cfgtuples), (void **)&cfgtuples);
	if (ntuples < 0)
		return (ENOENT);
	if (ntuples == 0)
		return (0); /* Empty property is not an error. */
	for (i = 0, cfg = cfgtuples; i < ntuples; i++, cfg++) {
		sion = (cfg->padconf_val & PADCONF_SION) ? PADMUX_SION : 0;
		WR4(sc, cfg->mux_reg, cfg->mux_val | sion);
		iomux_configure_input(sc, cfg->input_reg, cfg->input_val);
		if ((cfg->padconf_val & PADCONF_NONE) == 0)
			WR4(sc, cfg->padconf_reg, cfg->padconf_val);
		if (bootverbose) {
			char name[32]; 
			OF_getprop(cfgnode, "name", &name, sizeof(name));
			printf("%16s: muxreg 0x%04x muxval 0x%02x "
			    "inpreg 0x%04x inpval 0x%02x "
			    "padreg 0x%04x padval 0x%08x\n",
			    name, cfg->mux_reg, cfg->mux_val | sion,
			    cfg->input_reg, cfg->input_val,
			    cfg->padconf_reg, cfg->padconf_val);
		}
	}
	OF_prop_free(cfgtuples);
	return (0);
}