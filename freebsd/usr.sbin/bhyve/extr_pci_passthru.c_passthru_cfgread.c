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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int dummy; } ;
struct pci_devinst {struct passthru_softc* pi_arg; } ;
struct TYPE_2__ {scalar_t__ emulated; } ;
struct passthru_softc {int /*<<< orphan*/  psc_sel; TYPE_1__ psc_msi; } ;

/* Variables and functions */
 int PCIR_CAP_PTR ; 
 scalar_t__ bar_access (int) ; 
 scalar_t__ msicap_access (struct passthru_softc*,int) ; 
 int /*<<< orphan*/  read_config (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
passthru_cfgread(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
		 int coff, int bytes, uint32_t *rv)
{
	struct passthru_softc *sc;

	sc = pi->pi_arg;

	/*
	 * PCI BARs and MSI capability is emulated.
	 */
	if (bar_access(coff) || msicap_access(sc, coff))
		return (-1);

#ifdef LEGACY_SUPPORT
	/*
	 * Emulate PCIR_CAP_PTR if this device does not support MSI capability
	 * natively.
	 */
	if (sc->psc_msi.emulated) {
		if (coff >= PCIR_CAP_PTR && coff < PCIR_CAP_PTR + 4)
			return (-1);
	}
#endif

	/* Everything else just read from the device's config space */
	*rv = read_config(&sc->psc_sel, coff, bytes);

	return (0);
}