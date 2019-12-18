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
struct fxp_softc {scalar_t__ watchdog_timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  FXP_LOCK_ASSERT (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_watchdog(struct fxp_softc *sc)
{
	if_t ifp = sc->ifp;

	FXP_LOCK_ASSERT(sc, MA_OWNED);

	if (sc->watchdog_timer == 0 || --sc->watchdog_timer)
		return;

	device_printf(sc->dev, "device timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
	fxp_init_body(sc, 1);
}