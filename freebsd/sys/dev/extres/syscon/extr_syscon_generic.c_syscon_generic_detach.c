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
struct syscon_generic_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * syscon; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSCON ; 
 int /*<<< orphan*/  SYSCON_LOCK_DESTROY (struct syscon_generic_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct syscon_generic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
syscon_generic_detach(device_t dev)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	if (sc->syscon != NULL) {
		syscon_unregister(sc->syscon);
		free(sc->syscon, M_SYSCON);
	}

	SYSCON_LOCK_DESTROY(sc);

	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	return (0);
}