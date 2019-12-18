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
struct vtbe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTBE_LOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  VTBE_UNLOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  vtbe_init_locked (struct vtbe_softc*) ; 

__attribute__((used)) static void
vtbe_init(void *if_softc)
{
	struct vtbe_softc *sc = if_softc;

	VTBE_LOCK(sc);
	vtbe_init_locked(sc);
	VTBE_UNLOCK(sc);
}