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
struct sfxge_intr {int n_alloc; struct sfxge_intr_hdl* table; } ;
struct sfxge_softc {int /*<<< orphan*/  dev; struct sfxge_intr intr; } ;
struct sfxge_intr_hdl {int /*<<< orphan*/  eih_tag; int /*<<< orphan*/  eih_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfxge_intr_bus_disable(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	struct sfxge_intr_hdl *table;
	int i;

	intr = &sc->intr;
	table = intr->table;

	/* Remove all handlers */
	for (i = 0; i < intr->n_alloc; i++)
		bus_teardown_intr(sc->dev, table[i].eih_res,
		    table[i].eih_tag);
}