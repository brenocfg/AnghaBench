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
struct vga_resource {int dummy; } ;
struct vga_pci_softc {struct vga_resource* vga_bars; struct vga_resource vga_bios; } ;

/* Variables and functions */
 int PCIR_BIOS ; 
 int PCIR_MAX_BAR_0 ; 
 int PCI_RID2BAR (int) ; 

__attribute__((used)) static struct vga_resource *
lookup_res(struct vga_pci_softc *sc, int rid)
{
	int bar;

	if (rid == PCIR_BIOS)
		return (&sc->vga_bios);
	bar = PCI_RID2BAR(rid);
	if (bar >= 0 && bar <= PCIR_MAX_BAR_0)
		return (&sc->vga_bars[bar]);
	return (NULL);
}