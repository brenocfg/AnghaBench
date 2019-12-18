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
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_MISC ; 
 int /*<<< orphan*/  GDT_MPR_SEMA0 ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gdt_mpr_set_sema0(struct gdt_softc *gdt)
{
    GDT_DPRINTF(GDT_D_MISC, ("gdt_mpr_set_sema0(%p) ", gdt));

    bus_write_1(gdt->sc_dpmem, GDT_MPR_SEMA0, 1);
}