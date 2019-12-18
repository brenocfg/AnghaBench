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
struct an_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int /*<<< orphan*/  an_init_locked (struct an_softc*) ; 

__attribute__((used)) static void
an_init(void *xsc)
{
	struct an_softc		*sc = xsc;

	AN_LOCK(sc);
	an_init_locked(sc);
	AN_UNLOCK(sc);
}