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
struct bxe_softc {int /*<<< orphan*/  periodic_callout; int /*<<< orphan*/  periodic_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERIODIC_STOP ; 
 int /*<<< orphan*/  atomic_store_rel_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_periodic_stop(struct bxe_softc *sc)
{
    atomic_store_rel_long(&sc->periodic_flags, PERIODIC_STOP);
    callout_drain(&sc->periodic_callout);
}