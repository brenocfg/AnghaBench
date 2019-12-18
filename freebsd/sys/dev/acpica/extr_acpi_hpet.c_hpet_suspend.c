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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

__attribute__((used)) static int
hpet_suspend(device_t dev)
{
//	struct hpet_softc *sc;

	/*
	 * Disable the timer during suspend.  The timer will not lose
	 * its state in S1 or S2, but we are required to disable
	 * it.
	 */
//	sc = device_get_softc(dev);
//	hpet_disable(sc);

	return (0);
}