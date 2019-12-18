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
struct ow_softc {int /*<<< orphan*/ * owner; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int OWN_DONTWAIT ; 
 int /*<<< orphan*/  OW_ASSERT_UNLOCKED (struct ow_softc*) ; 
 int /*<<< orphan*/  OW_LOCK (struct ow_softc*) ; 
 int /*<<< orphan*/  OW_UNLOCK (struct ow_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct ow_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct ow_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_acquire_bus(device_t ndev, device_t pdev, int how)
{
	struct ow_softc *sc;

	sc = device_get_softc(ndev);
	OW_ASSERT_UNLOCKED(sc);
	OW_LOCK(sc);
	if (sc->owner != NULL) {
		if (sc->owner == pdev)
			panic("%s: %s recursively acquiring the bus.\n",
			    device_get_nameunit(ndev),
			    device_get_nameunit(pdev));
		if (how == OWN_DONTWAIT) {
			OW_UNLOCK(sc);
			return EWOULDBLOCK;
		}
		while (sc->owner != NULL)
			mtx_sleep(sc, &sc->mtx, 0, "owbuswait", 0);
	}
	sc->owner = pdev;
	OW_UNLOCK(sc);

	return 0;
}