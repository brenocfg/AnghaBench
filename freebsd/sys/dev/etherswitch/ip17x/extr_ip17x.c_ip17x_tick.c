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
struct ip17x_softc {int /*<<< orphan*/  callout_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ip17x_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ip17x_miipollstat (struct ip17x_softc*) ; 

__attribute__((used)) static void
ip17x_tick(void *arg)
{
	struct ip17x_softc *sc;

	sc = arg;
	ip17x_miipollstat(sc);
	callout_reset(&sc->callout_tick, hz, ip17x_tick, sc);
}