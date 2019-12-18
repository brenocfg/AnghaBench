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
struct gdt_softc {int sc_state; int /*<<< orphan*/  sc_free_gccb; int /*<<< orphan*/  sc_pending_gccb; int /*<<< orphan*/  sc_lock; } ;
struct gdt_ccb {int /*<<< orphan*/  gc_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_index_act; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_QUEUE ; 
 int /*<<< orphan*/  GDT_GCF_UNUSED ; 
 int GDT_SHUTDOWN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct gdt_ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdt_ccb ; 
 TYPE_1__ gdt_stat ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sle ; 
 int /*<<< orphan*/  wakeup (struct gdt_ccb*) ; 

void
gdt_free_ccb(struct gdt_softc *gdt, struct gdt_ccb *gccb)
{

    GDT_DPRINTF(GDT_D_QUEUE, ("gdt_free_ccb(%p, %p)\n", gdt, gccb));

    mtx_assert(&gdt->sc_lock, MA_OWNED);
    gccb->gc_flags = GDT_GCF_UNUSED;
    SLIST_REMOVE(&gdt->sc_pending_gccb, gccb, gdt_ccb, sle);
    SLIST_INSERT_HEAD(&gdt->sc_free_gccb, gccb, sle);
    --gdt_stat.cmd_index_act;
    if (gdt->sc_state & GDT_SHUTDOWN)
        wakeup(gccb);
}