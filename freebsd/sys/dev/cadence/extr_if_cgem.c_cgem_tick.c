#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mii_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ rx_frames; } ;
struct cgem_softc {scalar_t__ rx_frames_prev; int net_ctl_shadow; int /*<<< orphan*/  tick_ch; TYPE_1__ stats; scalar_t__ rxhangwar; int /*<<< orphan*/ * miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_NET_CTRL ; 
 int CGEM_NET_CTRL_RX_EN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  WR4 (struct cgem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_poll_hw_stats (struct cgem_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
cgem_tick(void *arg)
{
	struct cgem_softc *sc = (struct cgem_softc *)arg;
	struct mii_data *mii;

	CGEM_ASSERT_LOCKED(sc);

	/* Poll the phy. */
	if (sc->miibus != NULL) {
		mii = device_get_softc(sc->miibus);
		mii_tick(mii);
	}

	/* Poll statistics registers. */
	cgem_poll_hw_stats(sc);

	/* Check for receiver hang. */
	if (sc->rxhangwar && sc->rx_frames_prev == sc->stats.rx_frames) {
		/*
		 * Reset receiver logic by toggling RX_EN bit.  1usec
		 * delay is necessary especially when operating at 100mbps
		 * and 10mbps speeds.
		 */
		WR4(sc, CGEM_NET_CTRL, sc->net_ctl_shadow &
		    ~CGEM_NET_CTRL_RX_EN);
		DELAY(1);
		WR4(sc, CGEM_NET_CTRL, sc->net_ctl_shadow);
	}
	sc->rx_frames_prev = sc->stats.rx_frames;

	/* Next callout in one second. */
	callout_reset(&sc->tick_ch, hz, cgem_tick, sc);
}