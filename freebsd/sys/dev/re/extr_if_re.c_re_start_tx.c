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
struct TYPE_2__ {int /*<<< orphan*/  rl_tx_list_map; int /*<<< orphan*/  rl_tx_list_tag; } ;
struct rl_softc {int rl_watchdog_timer; int /*<<< orphan*/  rl_txstart; TYPE_1__ rl_ldata; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RL_TIMERCNT ; 
 int /*<<< orphan*/  RL_TXSTART_START ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
re_start_tx(struct rl_softc *sc)
{

	/* Flush the TX descriptors */
	bus_dmamap_sync(sc->rl_ldata.rl_tx_list_tag,
	    sc->rl_ldata.rl_tx_list_map,
	    BUS_DMASYNC_PREWRITE|BUS_DMASYNC_PREREAD);

	CSR_WRITE_1(sc, sc->rl_txstart, RL_TXSTART_START);

#ifdef RE_TX_MODERATION
	/*
	 * Use the countdown timer for interrupt moderation.
	 * 'TX done' interrupts are disabled. Instead, we reset the
	 * countdown timer, which will begin counting until it hits
	 * the value in the TIMERINT register, and then trigger an
	 * interrupt. Each time we write to the TIMERCNT register,
	 * the timer count is reset to 0.
	 */
	CSR_WRITE_4(sc, RL_TIMERCNT, 1);
#endif

	/*
	 * Set a timeout in case the chip goes out to lunch.
	 */
	sc->rl_watchdog_timer = 5;
}