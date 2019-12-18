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
struct vtnet_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_CORE_LOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_UNLOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_init_locked (struct vtnet_softc*) ; 

__attribute__((used)) static void
vtnet_init(void *xsc)
{
	struct vtnet_softc *sc;

	sc = xsc;

	VTNET_CORE_LOCK(sc);
	vtnet_init_locked(sc);
	VTNET_CORE_UNLOCK(sc);
}