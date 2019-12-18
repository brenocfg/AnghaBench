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
struct gdt_softc {scalar_t__ (* sc_test_busy ) (struct gdt_softc*) ;int /*<<< orphan*/  sc_state; } ;
struct gdt_ccb {scalar_t__ gc_cmd_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_INIT ; 
 int /*<<< orphan*/  GDT_POLL_WAIT ; 
 scalar_t__ iir_intr_locked (struct gdt_softc*) ; 
 scalar_t__ stub1 (struct gdt_softc*) ; 

__attribute__((used)) static int
gdt_wait(struct gdt_softc *gdt, struct gdt_ccb *gccb, 
         int timeout)
{
    int rv = 0;

    GDT_DPRINTF(GDT_D_INIT,
                ("gdt_wait(%p, %p, %d)\n", gdt, gccb, timeout));

    gdt->sc_state |= GDT_POLL_WAIT;
    do {
        if (iir_intr_locked(gdt) == gccb->gc_cmd_index) {
            rv = 1;
            break;
        }
        DELAY(1);
    } while (--timeout);
    gdt->sc_state &= ~GDT_POLL_WAIT;
    
    while (gdt->sc_test_busy(gdt))
        DELAY(1);               /* XXX correct? */

    return (rv);
}