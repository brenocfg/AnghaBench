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
struct sfxge_intr {scalar_t__ state; int n_alloc; int /*<<< orphan*/  type; struct sfxge_intr_hdl* table; int /*<<< orphan*/ * msix_res; int /*<<< orphan*/  status; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/  dev; } ;
struct sfxge_intr_hdl {scalar_t__ eih_rid; int /*<<< orphan*/  eih_res; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_INTR_INVALID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 scalar_t__ SFXGE_INTR_UNINITIALIZED ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sfxge_intr_hdl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_intr_teardown_msix (struct sfxge_softc*) ; 

void
sfxge_intr_fini(struct sfxge_softc *sc)
{
	struct sfxge_intr_hdl *table;
	struct sfxge_intr *intr;
	efsys_mem_t *esmp;
	device_t dev;
	int i;

	dev = sc->dev;
	intr = &sc->intr;
	esmp = &intr->status;
	table = intr->table;

	KASSERT(intr->state == SFXGE_INTR_INITIALIZED,
	    ("intr->state != SFXGE_INTR_INITIALIZED"));

	/* Free DMA memory. */
	sfxge_dma_free(esmp);

	/* Free interrupt handles. */
	for (i = 0; i < intr->n_alloc; i++)
		bus_release_resource(dev, SYS_RES_IRQ,
		    table[i].eih_rid, table[i].eih_res);

	if (table[0].eih_rid != 0)
		pci_release_msi(dev);

	if (intr->msix_res != NULL)
		sfxge_intr_teardown_msix(sc);

	/* Free the handle table */
	free(table, M_SFXGE);
	intr->table = NULL;
	intr->n_alloc = 0;

	/* Clear the interrupt type */
	intr->type = EFX_INTR_INVALID;

	intr->state = SFXGE_INTR_UNINITIALIZED;
}