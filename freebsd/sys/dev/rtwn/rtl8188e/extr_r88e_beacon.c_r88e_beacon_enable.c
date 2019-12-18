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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88E_MBID_TXBCN_RPT (int) ; 
 int /*<<< orphan*/  R92C_BCN_CTRL (int) ; 
 int /*<<< orphan*/  R92C_BCN_CTRL_EN_BCN ; 
 int /*<<< orphan*/  R92C_MBID_NUM ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r88e_beacon_enable(struct rtwn_softc *sc, int id, int enable)
{

	if (enable) {
		rtwn_setbits_1(sc, R92C_MBID_NUM, 0, R88E_MBID_TXBCN_RPT(id));
		rtwn_setbits_1(sc, R92C_BCN_CTRL(id),
		    0, R92C_BCN_CTRL_EN_BCN);
	} else {
		rtwn_setbits_1(sc, R92C_MBID_NUM, R88E_MBID_TXBCN_RPT(id), 0);
		rtwn_setbits_1(sc, R92C_BCN_CTRL(id),
		    R92C_BCN_CTRL_EN_BCN, 0);
	}
}