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
struct ukswitch_softc {int /*<<< orphan*/  callout_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ukswitch_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ukswitch_miipollstat (struct ukswitch_softc*) ; 

__attribute__((used)) static void
ukswitch_tick(void *arg)
{
	struct ukswitch_softc *sc = arg;

	ukswitch_miipollstat(sc);
	callout_reset(&sc->callout_tick, hz, ukswitch_tick, sc);
}