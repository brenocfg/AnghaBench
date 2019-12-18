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
struct ale_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_UNLOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_init_locked (struct ale_softc*) ; 

__attribute__((used)) static void
ale_init(void *xsc)
{
	struct ale_softc *sc;

	sc = (struct ale_softc *)xsc;
	ALE_LOCK(sc);
	ale_init_locked(sc);
	ALE_UNLOCK(sc);
}