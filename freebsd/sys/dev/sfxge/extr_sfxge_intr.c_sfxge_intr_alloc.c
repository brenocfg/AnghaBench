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
struct sfxge_intr {struct sfxge_intr_hdl* table; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/  dev; } ;
struct sfxge_intr_hdl {int eih_rid; struct resource* eih_res; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_SFXGE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct sfxge_intr_hdl* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sfxge_intr_alloc(struct sfxge_softc *sc, int count)
{
	device_t dev;
	struct sfxge_intr_hdl *table;
	struct sfxge_intr *intr;
	struct resource *res;
	int rid;
	int error;
	int i;

	dev = sc->dev;
	intr = &sc->intr;
	error = 0;

	table = malloc(count * sizeof(struct sfxge_intr_hdl),
	    M_SFXGE, M_WAITOK);
	intr->table = table;

	for (i = 0; i < count; i++) {
		rid = i + 1;
		res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
		    RF_SHAREABLE | RF_ACTIVE);
		if (res == NULL) {
			device_printf(dev, "Couldn't allocate interrupts for "
			    "message %d\n", rid);
			error = ENOMEM;
			break;
		}
		table[i].eih_rid = rid;
		table[i].eih_res = res;
	}

	if (error != 0) {
		count = i - 1;
		for (i = 0; i < count; i++)
			bus_release_resource(dev, SYS_RES_IRQ,
			    table[i].eih_rid, table[i].eih_res);
	}

	return (error);
}