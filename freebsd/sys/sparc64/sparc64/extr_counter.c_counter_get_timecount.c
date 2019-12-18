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
struct timecounter {struct ct_softc* tc_priv; } ;
struct ct_softc {int /*<<< orphan*/  sc_offset; int /*<<< orphan*/  sc_handle; int /*<<< orphan*/  sc_tag; } ;

/* Variables and functions */
 unsigned int bus_space_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
counter_get_timecount(struct timecounter *tc)
{
	struct ct_softc *sc;

	sc = tc->tc_priv;
	return (bus_space_read_8(sc->sc_tag, sc->sc_handle, sc->sc_offset));
}