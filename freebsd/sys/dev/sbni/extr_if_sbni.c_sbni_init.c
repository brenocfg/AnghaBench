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
struct sbni_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBNI_LOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  SBNI_UNLOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_init_locked (struct sbni_softc*) ; 

__attribute__((used)) static void
sbni_init(void *xsc)
{
	struct sbni_softc *sc;

	sc = (struct sbni_softc *)xsc;
	SBNI_LOCK(sc);
	sbni_init_locked(sc);
	SBNI_UNLOCK(sc);
}