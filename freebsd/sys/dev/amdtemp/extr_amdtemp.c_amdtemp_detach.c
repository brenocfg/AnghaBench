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
struct amdtemp_softc {int sc_ncores; int /*<<< orphan*/ ** sc_sysctl_cpu; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct amdtemp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_remove_oid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
amdtemp_detach(device_t dev)
{
	struct amdtemp_softc *sc = device_get_softc(dev);
	int i;

	for (i = 0; i < sc->sc_ncores; i++)
		if (sc->sc_sysctl_cpu[i] != NULL)
			sysctl_remove_oid(sc->sc_sysctl_cpu[i], 1, 0);

	/* NewBus removes the dev.amdtemp.N tree by itself. */

	return (0);
}