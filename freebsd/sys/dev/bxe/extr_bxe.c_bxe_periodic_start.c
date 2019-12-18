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
 int /*<<< orphan*/  PERIODIC_GO ; 
 int /*<<< orphan*/  atomic_store_rel_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_periodic_callout_func ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bxe_softc*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
bxe_periodic_start(struct bxe_softc *sc)
{
    atomic_store_rel_long(&sc->periodic_flags, PERIODIC_GO);
    callout_reset(&sc->periodic_callout, hz, bxe_periodic_callout_func, sc);
}