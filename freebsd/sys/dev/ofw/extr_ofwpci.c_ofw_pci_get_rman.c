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
typedef  int u_int ;
struct rman {int dummy; } ;
struct ofw_pci_softc {struct rman sc_mem_rman; struct rman sc_pmem_rman; int /*<<< orphan*/  sc_have_pmem; struct rman sc_io_rman; } ;

/* Variables and functions */
 int RF_PREFETCHABLE ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 

__attribute__((used)) static struct rman *
ofw_pci_get_rman(struct ofw_pci_softc *sc, int type, u_int flags)
{

	switch (type) {
	case SYS_RES_IOPORT:
		return (&sc->sc_io_rman);
	case SYS_RES_MEMORY:
		if (sc->sc_have_pmem  && (flags & RF_PREFETCHABLE))
			return (&sc->sc_pmem_rman);
		else
			return (&sc->sc_mem_rman);
	default:
		break;
	}

	return (NULL);
}