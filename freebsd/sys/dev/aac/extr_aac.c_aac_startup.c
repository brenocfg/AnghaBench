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
struct aac_softc {int /*<<< orphan*/  aac_ich; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_state; int /*<<< orphan*/  aac_io_lock; } ;
struct aac_mntinforesp {int MntRespCount; } ;
struct aac_fib {int dummy; } ;

/* Variables and functions */
 int AAC_MAX_CONTAINERS ; 
 int /*<<< orphan*/  AAC_STATE_SUSPEND ; 
 int /*<<< orphan*/  AAC_UNMASK_INTERRUPTS (struct aac_softc*) ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_add_container (struct aac_softc*,struct aac_mntinforesp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_alloc_sync_fib (struct aac_softc*,struct aac_fib**) ; 
 struct aac_mntinforesp* aac_get_container_info (struct aac_softc*,struct aac_fib*,int) ; 
 int /*<<< orphan*/  aac_release_sync_fib (struct aac_softc*) ; 
 scalar_t__ bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aac_startup(void *arg)
{
	struct aac_softc *sc;
	struct aac_fib *fib;
	struct aac_mntinforesp *mir;
	int count = 0, i = 0;

	sc = (struct aac_softc *)arg;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_io_lock);
	aac_alloc_sync_fib(sc, &fib);

	/* loop over possible containers */
	do {
		if ((mir = aac_get_container_info(sc, fib, i)) == NULL)
			continue;
		if (i == 0)
			count = mir->MntRespCount;
		aac_add_container(sc, mir, 0);
		i++;
	} while ((i < count) && (i < AAC_MAX_CONTAINERS));

	aac_release_sync_fib(sc);
	mtx_unlock(&sc->aac_io_lock);

	/* mark the controller up */
	sc->aac_state &= ~AAC_STATE_SUSPEND;

	/* poke the bus to actually attach the child devices */
	if (bus_generic_attach(sc->aac_dev))
		device_printf(sc->aac_dev, "bus_generic_attach failed\n");

	/* disconnect ourselves from the intrhook chain */
	config_intrhook_disestablish(&sc->aac_ich);

	/* enable interrupts now */
	AAC_UNMASK_INTERRUPTS(sc);
}