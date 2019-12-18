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
struct stge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_init_locked (struct stge_softc*) ; 

__attribute__((used)) static void
stge_init(void *xsc)
{
	struct stge_softc *sc;

	sc = (struct stge_softc *)xsc;
	STGE_LOCK(sc);
	stge_init_locked(sc);
	STGE_UNLOCK(sc);
}