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
struct pl310_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int AUX_CTRL_DATA_PREFETCH ; 
 int AUX_CTRL_EARLY_BRESP ; 
 int AUX_CTRL_INSTR_PREFETCH ; 
 int AUX_CTRL_NS_INT_CTRL ; 
 int AUX_CTRL_NS_LOCKDOWN ; 
 int AUX_CTRL_SHARE_OVERRIDE ; 
 int /*<<< orphan*/  PL310_AUX_CTRL ; 
 int /*<<< orphan*/  PL310_PREFETCH_CTRL ; 
 int PREFETCH_CTRL_DATA_PREFETCH ; 
 int PREFETCH_CTRL_DL ; 
 int PREFETCH_CTRL_DL_ON_WRAP ; 
 int PREFETCH_CTRL_INCR_DL ; 
 int PREFETCH_CTRL_INSTR_PREFETCH ; 
 int PREFETCH_CTRL_NOTSAMEID ; 
 int PREFETCH_CTRL_OFFSET_MASK ; 
 int PREFETCH_CTRL_PREFETCH_DROP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pl310_read4 (struct pl310_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pl310_print_config(struct pl310_softc *sc)
{
	uint32_t aux, prefetch;
	const char *dis = "disabled";
	const char *ena = "enabled";

	aux = pl310_read4(sc, PL310_AUX_CTRL);
	prefetch = pl310_read4(sc, PL310_PREFETCH_CTRL);

	device_printf(sc->sc_dev, "Early BRESP response: %s\n",
		(aux & AUX_CTRL_EARLY_BRESP) ? ena : dis);
	device_printf(sc->sc_dev, "Instruction prefetch: %s\n",
		(aux & AUX_CTRL_INSTR_PREFETCH) ? ena : dis);
	device_printf(sc->sc_dev, "Data prefetch: %s\n",
		(aux & AUX_CTRL_DATA_PREFETCH) ? ena : dis);
	device_printf(sc->sc_dev, "Non-secure interrupt control: %s\n",
		(aux & AUX_CTRL_NS_INT_CTRL) ? ena : dis);
	device_printf(sc->sc_dev, "Non-secure lockdown: %s\n",
		(aux & AUX_CTRL_NS_LOCKDOWN) ? ena : dis);
	device_printf(sc->sc_dev, "Share override: %s\n",
		(aux & AUX_CTRL_SHARE_OVERRIDE) ? ena : dis);

	device_printf(sc->sc_dev, "Double linefill: %s\n",
		(prefetch & PREFETCH_CTRL_DL) ? ena : dis);
	device_printf(sc->sc_dev, "Instruction prefetch: %s\n",
		(prefetch & PREFETCH_CTRL_INSTR_PREFETCH) ? ena : dis);
	device_printf(sc->sc_dev, "Data prefetch: %s\n",
		(prefetch & PREFETCH_CTRL_DATA_PREFETCH) ? ena : dis);
	device_printf(sc->sc_dev, "Double linefill on WRAP request: %s\n",
		(prefetch & PREFETCH_CTRL_DL_ON_WRAP) ? ena : dis);
	device_printf(sc->sc_dev, "Prefetch drop: %s\n",
		(prefetch & PREFETCH_CTRL_PREFETCH_DROP) ? ena : dis);
	device_printf(sc->sc_dev, "Incr double Linefill: %s\n",
		(prefetch & PREFETCH_CTRL_INCR_DL) ? ena : dis);
	device_printf(sc->sc_dev, "Not same ID on exclusive sequence: %s\n",
		(prefetch & PREFETCH_CTRL_NOTSAMEID) ? ena : dis);
	device_printf(sc->sc_dev, "Prefetch offset: %d\n",
		(prefetch & PREFETCH_CTRL_OFFSET_MASK));
}