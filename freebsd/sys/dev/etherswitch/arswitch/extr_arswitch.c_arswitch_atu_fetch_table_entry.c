#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; int /*<<< orphan*/ * entries; } ;
struct arswitch_softc {TYPE_1__ atu; } ;
struct TYPE_6__ {int id; } ;
typedef  TYPE_2__ etherswitch_atu_entry_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int ENOENT ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
arswitch_atu_fetch_table_entry(device_t dev, etherswitch_atu_entry_t *e)
{
	struct arswitch_softc *sc;
	int id;

	sc = device_get_softc(dev);
	id = e->id;

	ARSWITCH_LOCK(sc);
	if (id > sc->atu.count) {
		ARSWITCH_UNLOCK(sc);
		return (ENOENT);
	}

	memcpy(e, &sc->atu.entries[id], sizeof(*e));
	ARSWITCH_UNLOCK(sc);
	return (0);
}