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
struct imx6_anatop_softc {int dummy; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  tempmon_goslow (struct imx6_anatop_softc*) ; 

__attribute__((used)) static int
tempmon_intr(void *arg)
{
	struct imx6_anatop_softc *sc = arg;

	/*
	 * XXX Note that this code doesn't currently run (for some mysterious
	 * reason we just never get an interrupt), so the real monitoring is
	 * done by tempmon_throttle_check().
	 */
	tempmon_goslow(sc);
	/* XXX Schedule callout to speed back up eventually. */
	return (FILTER_HANDLED);
}