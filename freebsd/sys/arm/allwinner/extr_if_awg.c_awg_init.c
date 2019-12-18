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
struct awg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_init_locked (struct awg_softc*) ; 

__attribute__((used)) static void
awg_init(void *softc)
{
	struct awg_softc *sc;

	sc = softc;

	AWG_LOCK(sc);
	awg_init_locked(sc);
	AWG_UNLOCK(sc);
}