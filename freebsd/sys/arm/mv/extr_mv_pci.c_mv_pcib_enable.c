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
struct mv_pcib_softc {scalar_t__ sc_skip_enable_procedure; scalar_t__ sc_mode; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONTROL ; 
 int CPU_CONTROL_PCIE_DISABLE (int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ MV_MODE_ROOT ; 
 int PCIE_LINK_TIMEOUT ; 
 int /*<<< orphan*/  PCIE_REG_STATUS ; 
 int PCIE_STATUS_LINK_DOWN ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int PCIM_CMD_SERRESPEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_pcib_enable(struct mv_pcib_softc *sc, uint32_t unit)
{
	uint32_t val;
	int timeout;

	if (sc->sc_skip_enable_procedure)
		goto pcib_enable_root_mode;

	/*
	 * Check if PCIE device is enabled.
	 */
	if ((sc->sc_skip_enable_procedure == 0) &&
	    (read_cpu_ctrl(CPU_CONTROL) & CPU_CONTROL_PCIE_DISABLE(unit))) {
		write_cpu_ctrl(CPU_CONTROL, read_cpu_ctrl(CPU_CONTROL) &
		    ~(CPU_CONTROL_PCIE_DISABLE(unit)));

		timeout = PCIE_LINK_TIMEOUT;
		val = bus_space_read_4(sc->sc_bst, sc->sc_bsh,
		    PCIE_REG_STATUS);
		while (((val & PCIE_STATUS_LINK_DOWN) == 1) && (timeout > 0)) {
			DELAY(1000);
			timeout -= 1000;
			val = bus_space_read_4(sc->sc_bst, sc->sc_bsh,
			    PCIE_REG_STATUS);
		}
	}

pcib_enable_root_mode:
	if (sc->sc_mode == MV_MODE_ROOT) {
		/*
		 * Enable PCI bridge.
		 */
		val = bus_space_read_4(sc->sc_bst, sc->sc_bsh, PCIR_COMMAND);
		val |= PCIM_CMD_SERRESPEN | PCIM_CMD_BUSMASTEREN |
		    PCIM_CMD_MEMEN | PCIM_CMD_PORTEN;
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, PCIR_COMMAND, val);
	}
}