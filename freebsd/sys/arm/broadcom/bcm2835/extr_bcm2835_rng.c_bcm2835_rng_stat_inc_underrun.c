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
struct bcm2835_rng_softc {int /*<<< orphan*/  sc_underrun; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline void
bcm2835_rng_stat_inc_underrun(struct bcm2835_rng_softc *sc)
{

	atomic_add_long(&sc->sc_underrun, 1);
}