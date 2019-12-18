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
struct ow_softc {int /*<<< orphan*/ * owner; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OW_ASSERT_UNLOCKED (struct ow_softc*) ; 
 int /*<<< orphan*/  OW_LOCK (struct ow_softc*) ; 
 int /*<<< orphan*/  OW_UNLOCK (struct ow_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct ow_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wakeup (struct ow_softc*) ; 

__attribute__((used)) static void
ow_release_bus(device_t ndev, device_t pdev)
{
	struct ow_softc *sc;

	sc = device_get_softc(ndev);
	OW_ASSERT_UNLOCKED(sc);
	OW_LOCK(sc);
	if (sc->owner == NULL)
		panic("%s: %s releasing unowned bus.", device_get_nameunit(ndev),
		    device_get_nameunit(pdev));
	if (sc->owner != pdev)
		panic("%s: %s don't own the bus. %s does. game over.",
		    device_get_nameunit(ndev), device_get_nameunit(pdev),
		    device_get_nameunit(sc->owner));
	sc->owner = NULL;
	wakeup(sc);
	OW_UNLOCK(sc);
}