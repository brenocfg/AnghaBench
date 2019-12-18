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
struct ieee80211com {int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; int /*<<< orphan*/  ic_ioctl; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_set_led; struct r12a_softc* sc_priv; struct ieee80211com sc_ic; } ;
struct r12a_softc {scalar_t__ board_type; int /*<<< orphan*/  rs_scan_end; int /*<<< orphan*/  rs_scan_start; int /*<<< orphan*/  rs_chan_check; } ;

/* Variables and functions */
 scalar_t__ R92C_BOARD_TYPE_COMBO ; 
 scalar_t__ R92C_BOARD_TYPE_MINICARD ; 
 scalar_t__ R92C_BOARD_TYPE_SOLO ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtwn_softc*) ; 
 int /*<<< orphan*/  r12a_ioctl_net ; 
 int /*<<< orphan*/  r21a_set_led ; 
 int /*<<< orphan*/  r21au_chan_check ; 
 int /*<<< orphan*/  r21au_scan_end ; 
 int /*<<< orphan*/  r21au_scan_start ; 
 int /*<<< orphan*/  r88e_set_led ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
r21a_postattach(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct r12a_softc *rs = sc->sc_priv;

	if (rs->board_type == R92C_BOARD_TYPE_MINICARD ||
	    rs->board_type == R92C_BOARD_TYPE_SOLO ||
	    rs->board_type == R92C_BOARD_TYPE_COMBO)
		sc->sc_set_led = r88e_set_led;
	else
		sc->sc_set_led = r21a_set_led;

	TIMEOUT_TASK_INIT(taskqueue_thread, &rs->rs_chan_check, 0,
	    r21au_chan_check, sc);

	/* RXCKSUM */
	ic->ic_ioctl = r12a_ioctl_net;
	/* DFS */
	rs->rs_scan_start = ic->ic_scan_start;
	ic->ic_scan_start = r21au_scan_start;
	rs->rs_scan_end = ic->ic_scan_end;
	ic->ic_scan_end = r21au_scan_end;
}