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
struct mmc_softc {int /*<<< orphan*/  config_intrhook; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_scan (struct mmc_softc*) ; 

__attribute__((used)) static void
mmc_delayed_attach(void *xsc)
{
	struct mmc_softc *sc = xsc;

	mmc_scan(sc);
	config_intrhook_disestablish(&sc->config_intrhook);
}