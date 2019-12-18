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
struct ata_request {size_t unit; int /*<<< orphan*/  parent; } ;
struct ata_macio_softc {int* udmaconf; int* wdmaconf; int* pioconf; int /*<<< orphan*/  sc_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_MACIO_TIMINGREG ; 
 int ata_begin_transaction (struct ata_request*) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ata_macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_macio_begin_transaction(struct ata_request *request)
{
	struct ata_macio_softc *sc = device_get_softc(request->parent);

	bus_write_4(sc->sc_mem, ATA_MACIO_TIMINGREG, 
	    sc->udmaconf[request->unit] | sc->wdmaconf[request->unit] 
	    | sc->pioconf[request->unit]); 

	return ata_begin_transaction(request);
}