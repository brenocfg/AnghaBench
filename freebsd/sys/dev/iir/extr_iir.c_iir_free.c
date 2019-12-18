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
struct gdt_softc {int sc_init_level; int /*<<< orphan*/  sc_parent_dmat; int /*<<< orphan*/  sc_buffer_dmat; int /*<<< orphan*/  sc_gcscratch_dmat; int /*<<< orphan*/  sc_gcscratch_dmamap; int /*<<< orphan*/  sc_gcscratch; TYPE_1__* sc_gccbs; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gc_dmamap; int /*<<< orphan*/  gc_timeout; int /*<<< orphan*/  gc_map_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_INIT ; 
 int /*<<< orphan*/  GDT_MAXCMDS ; 
 int /*<<< orphan*/  M_GDTBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdt_destroy_dev (int /*<<< orphan*/ ) ; 

void
iir_free(struct gdt_softc *gdt)
{
    int i;

    GDT_DPRINTF(GDT_D_INIT, ("iir_free()\n"));

    switch (gdt->sc_init_level) {
      default:
        gdt_destroy_dev(gdt->sc_dev);
      case 5:
        for (i = GDT_MAXCMDS-1; i >= 0; i--) 
            if (gdt->sc_gccbs[i].gc_map_flag) {
		callout_drain(&gdt->sc_gccbs[i].gc_timeout);
                bus_dmamap_destroy(gdt->sc_buffer_dmat,
                                   gdt->sc_gccbs[i].gc_dmamap);
	    }
        bus_dmamap_unload(gdt->sc_gcscratch_dmat, gdt->sc_gcscratch_dmamap);
        free(gdt->sc_gccbs, M_GDTBUF);
      case 4:
        bus_dmamem_free(gdt->sc_gcscratch_dmat, gdt->sc_gcscratch, gdt->sc_gcscratch_dmamap);
      case 3:
        bus_dma_tag_destroy(gdt->sc_gcscratch_dmat);
      case 2:
        bus_dma_tag_destroy(gdt->sc_buffer_dmat);
      case 1:
        bus_dma_tag_destroy(gdt->sc_parent_dmat);
      case 0:
        break;
    }
}