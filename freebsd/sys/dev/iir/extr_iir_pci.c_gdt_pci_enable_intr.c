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
struct gdt_softc {int /*<<< orphan*/  sc_dpmem; } ;

/* Variables and functions */
 int GDT_CLASS (struct gdt_softc*) ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_INTR ; 
 int /*<<< orphan*/  GDT_EDOOR_EN ; 
#define  GDT_MPR 128 
 int /*<<< orphan*/  GDT_MPR_EDOOR ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gdt_pci_enable_intr(struct gdt_softc *gdt)
{
    GDT_DPRINTF(GDT_D_INTR, ("gdt_pci_enable_intr(%p) ", gdt));

    switch(GDT_CLASS(gdt)) {
      case GDT_MPR:
        bus_write_1(gdt->sc_dpmem, GDT_MPR_EDOOR, 0xff);
        bus_write_1(gdt->sc_dpmem, GDT_EDOOR_EN,
	    bus_read_1(gdt->sc_dpmem, GDT_EDOOR_EN) & ~4);
        break;
    }
}