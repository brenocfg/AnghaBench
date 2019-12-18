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
struct rtl8366rb_softc {int /*<<< orphan*/  callout_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct rtl8366rb_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  rtl833rb_miipollstat (struct rtl8366rb_softc*) ; 

__attribute__((used)) static void
rtl8366rb_tick(void *arg)
{
	struct rtl8366rb_softc *sc;

	sc = arg;

	rtl833rb_miipollstat(sc);
	callout_reset(&sc->callout_tick, hz, rtl8366rb_tick, sc);
}