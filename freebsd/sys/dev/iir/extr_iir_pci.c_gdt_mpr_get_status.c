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
typedef  int /*<<< orphan*/  u_int8_t ;
struct gdt_softc {int /*<<< orphan*/  sc_dpmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_MISC ; 
 int /*<<< orphan*/  GDT_MPR_EDOOR ; 
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int8_t
gdt_mpr_get_status(struct gdt_softc *gdt)
{
    GDT_DPRINTF(GDT_D_MISC, ("gdt_mpr_get_status(%p) ", gdt));
        
    return bus_read_1(gdt->sc_dpmem, GDT_MPR_EDOOR);
}