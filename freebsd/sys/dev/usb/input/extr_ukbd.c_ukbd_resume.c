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
struct ukbd_softc {int /*<<< orphan*/  sc_kbd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 struct ukbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ukbd_clear_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ukbd_resume(device_t dev)
{
	struct ukbd_softc *sc = device_get_softc(dev);

	UKBD_LOCK_ASSERT();

	ukbd_clear_state(&sc->sc_kbd);

	return (0);
}