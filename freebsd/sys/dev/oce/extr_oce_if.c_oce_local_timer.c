#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nwqs; int /*<<< orphan*/  timer; int /*<<< orphan*/ * wq; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE (TYPE_1__*) ; 
 scalar_t__ IS_SH (TYPE_1__*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  oce_detect_hw_error (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_eqd_set_periodic (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_mac_addr_set (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_refresh_nic_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_refresh_queue_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_tx_restart (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oce_local_timer(void *arg)
{
	POCE_SOFTC sc = arg;
	int i = 0;
	
	oce_detect_hw_error(sc);
	oce_refresh_nic_stats(sc);
	oce_refresh_queue_stats(sc);
	oce_mac_addr_set(sc);
	
	/* TX Watch Dog*/
	for (i = 0; i < sc->nwqs; i++)
		oce_tx_restart(sc, sc->wq[i]);
	
	/* calculate and set the eq delay for optimal interrupt rate */
	if (IS_BE(sc) || IS_SH(sc))
		oce_eqd_set_periodic(sc);

	callout_reset(&sc->timer, hz, oce_local_timer, sc);
}