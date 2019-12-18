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
struct opcic_softc {int sc_flags; int /*<<< orphan*/  sc_base_addr; } ;
struct consdev {struct opcic_softc* cn_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCT_PCI_CON_FLAG_NONBLOCK ; 
 int OPCIC_FLAG_RSYS ; 
 int octeon_pci_console_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int opcic_rsys_cngetc (struct opcic_softc*) ; 

__attribute__((used)) static int
opcic_cngetc(struct consdev *cp)
{
	struct opcic_softc *sc;
	char ch;
	int rv;

	sc = cp->cn_arg;

#ifdef OCTEON_VENDOR_RADISYS
	if ((sc->sc_flags & OPCIC_FLAG_RSYS) != 0)
		return (opcic_rsys_cngetc(sc));
#endif

	rv = octeon_pci_console_read(sc->sc_base_addr, 0, &ch, 1,
	    OCT_PCI_CON_FLAG_NONBLOCK);
	if (rv != 1)
		return (-1);
	return (ch);
}