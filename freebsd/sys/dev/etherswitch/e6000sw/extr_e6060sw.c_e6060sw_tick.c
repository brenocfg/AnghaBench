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
struct e6060sw_softc {int /*<<< orphan*/  callout_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct e6060sw_softc*) ; 
 int /*<<< orphan*/  e6060sw_miipollstat (struct e6060sw_softc*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
e6060sw_tick(void *arg)
{
	struct e6060sw_softc *sc;

	sc = arg;

	e6060sw_miipollstat(sc);
	callout_reset(&sc->callout_tick, hz, e6060sw_tick, sc);
}