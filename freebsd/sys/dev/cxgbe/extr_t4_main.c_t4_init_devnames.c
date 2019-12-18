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
struct adapter {int /*<<< orphan*/ * names; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CHELSIO_T4 ; 
 int chip_id (struct adapter*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * devnames ; 
 int nitems (int /*<<< orphan*/ *) ; 

void
t4_init_devnames(struct adapter *sc)
{
	int id;

	id = chip_id(sc);
	if (id >= CHELSIO_T4 && id - CHELSIO_T4 < nitems(devnames))
		sc->names = &devnames[id - CHELSIO_T4];
	else {
		device_printf(sc->dev, "chip id %d is not supported.\n", id);
		sc->names = NULL;
	}
}