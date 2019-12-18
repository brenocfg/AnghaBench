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
struct gdt_softc {int dummy; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_CMD ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  iir_intr_locked (struct gdt_softc*) ; 

__attribute__((used)) static void     
iir_poll( struct cam_sim *sim )
{
    struct gdt_softc *gdt;

    gdt = (struct gdt_softc *)cam_sim_softc( sim );
    GDT_DPRINTF(GDT_D_CMD, ("iir_poll sim %p gdt %p\n", sim, gdt));
    iir_intr_locked(gdt);
}