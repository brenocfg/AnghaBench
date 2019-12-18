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
typedef  scalar_t__ uint8_t ;
struct mv_pcib_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIM_CMD_BUSMASTEREN ; 
 scalar_t__ PCIM_CMD_MEMEN ; 
 scalar_t__ PCIM_CMD_PORTEN ; 
 scalar_t__ PCIM_HDRTYPE ; 
 scalar_t__ PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 scalar_t__ PCIS_BRIDGE_PCI ; 
 int PCI_FUNCMAX ; 
 scalar_t__ PCI_MAXHDRTYPE ; 
 int mv_pcib_init_all_bars (struct mv_pcib_softc*,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  mv_pcib_init_bridge (struct mv_pcib_softc*,int,int,int) ; 
 scalar_t__ mv_pcib_read_config (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_pcib_write_config (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pcib_write_irq_mask (struct mv_pcib_softc*,int) ; 

__attribute__((used)) static int
mv_pcib_init(struct mv_pcib_softc *sc, int bus, int maxslot)
{
	int slot, func, maxfunc, error;
	uint8_t hdrtype, command, class, subclass;

	for (slot = 0; slot <= maxslot; slot++) {
		maxfunc = 0;
		for (func = 0; func <= maxfunc; func++) {
			hdrtype = mv_pcib_read_config(sc->sc_dev, bus, slot,
			    func, PCIR_HDRTYPE, 1);

			if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
				continue;

			if (func == 0 && (hdrtype & PCIM_MFDEV))
				maxfunc = PCI_FUNCMAX;

			command = mv_pcib_read_config(sc->sc_dev, bus, slot,
			    func, PCIR_COMMAND, 1);
			command &= ~(PCIM_CMD_MEMEN | PCIM_CMD_PORTEN);
			mv_pcib_write_config(sc->sc_dev, bus, slot, func,
			    PCIR_COMMAND, command, 1);

			error = mv_pcib_init_all_bars(sc, bus, slot, func,
			    hdrtype);

			if (error)
				return (error);

			command |= PCIM_CMD_BUSMASTEREN | PCIM_CMD_MEMEN |
			    PCIM_CMD_PORTEN;
			mv_pcib_write_config(sc->sc_dev, bus, slot, func,
			    PCIR_COMMAND, command, 1);

			/* Handle PCI-PCI bridges */
			class = mv_pcib_read_config(sc->sc_dev, bus, slot,
			    func, PCIR_CLASS, 1);
			subclass = mv_pcib_read_config(sc->sc_dev, bus, slot,
			    func, PCIR_SUBCLASS, 1);

			if (class != PCIC_BRIDGE ||
			    subclass != PCIS_BRIDGE_PCI)
				continue;

			mv_pcib_init_bridge(sc, bus, slot, func);
		}
	}

	/* Enable all ABCD interrupts */
	pcib_write_irq_mask(sc, (0xF << 24));

	return (0);
}