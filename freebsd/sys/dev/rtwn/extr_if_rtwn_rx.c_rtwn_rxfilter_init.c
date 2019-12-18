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
struct rtwn_softc {int rcr; } ;

/* Variables and functions */
 int R92C_RCR_AB ; 
 int R92C_RCR_AM ; 
 int R92C_RCR_APM ; 
 int R92C_RCR_APP_ICV ; 
 int R92C_RCR_APP_MIC ; 
 int R92C_RCR_APP_PHYSTS ; 
 int R92C_RCR_HTC_LOC_CTRL ; 
 int /*<<< orphan*/  R92C_RXFLTMAP1 ; 
 int /*<<< orphan*/  R92C_RXFLTMAP2 ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_rxfilter_update (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_set_multi (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
rtwn_rxfilter_init(struct rtwn_softc *sc)
{

	RTWN_ASSERT_LOCKED(sc);

	/* Setup multicast filter. */
	rtwn_set_multi(sc);

	/* Reject all control frames. */
	rtwn_write_2(sc, R92C_RXFLTMAP1, 0x0000);

	/* Reject all data frames. */
	rtwn_write_2(sc, R92C_RXFLTMAP2, 0x0000);

	/* Append generic Rx filter bits. */
	sc->rcr |= R92C_RCR_AM | R92C_RCR_AB | R92C_RCR_APM |
	    R92C_RCR_HTC_LOC_CTRL | R92C_RCR_APP_PHYSTS |
	    R92C_RCR_APP_ICV | R92C_RCR_APP_MIC;

	/* Update dynamic Rx filter parts. */
	rtwn_rxfilter_update(sc);
}