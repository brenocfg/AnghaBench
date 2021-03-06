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
struct are_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int /*<<< orphan*/  are_init_locked (struct are_softc*) ; 

__attribute__((used)) static void
are_init(void *xsc)
{
	struct are_softc	 *sc = xsc;

	ARE_LOCK(sc);
	are_init_locked(sc);
	ARE_UNLOCK(sc);
}