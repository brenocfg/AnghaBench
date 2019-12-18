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
struct gdt_softc {int /*<<< orphan*/  sc_pending_gccb; int /*<<< orphan*/  sc_free_gccb; int /*<<< orphan*/  sc_lock; } ;
struct gdt_ccb {int dummy; } ;
struct TYPE_2__ {scalar_t__ cmd_index_act; scalar_t__ cmd_index_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_QUEUE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct gdt_ccb* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ gdt_stat ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sle ; 

__attribute__((used)) static struct gdt_ccb *
gdt_get_ccb(struct gdt_softc *gdt)
{
    struct gdt_ccb *gccb;
    
    GDT_DPRINTF(GDT_D_QUEUE, ("gdt_get_ccb(%p)\n", gdt));

    mtx_assert(&gdt->sc_lock, MA_OWNED);
    gccb = SLIST_FIRST(&gdt->sc_free_gccb);
    if (gccb != NULL) {
        SLIST_REMOVE_HEAD(&gdt->sc_free_gccb, sle);
        SLIST_INSERT_HEAD(&gdt->sc_pending_gccb, gccb, sle);
        ++gdt_stat.cmd_index_act;
        if (gdt_stat.cmd_index_act > gdt_stat.cmd_index_max)
            gdt_stat.cmd_index_max = gdt_stat.cmd_index_act;
    }
    return (gccb);
}