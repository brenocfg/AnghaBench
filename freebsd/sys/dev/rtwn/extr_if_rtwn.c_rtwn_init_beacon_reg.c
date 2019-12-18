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
 int /*<<< orphan*/  R92C_BCNDMATIM ; 
 int /*<<< orphan*/  R92C_BCNTCFG ; 
 int /*<<< orphan*/  R92C_BCN_CTRL (int) ; 
 int R92C_BCN_CTRL_DIS_TSF_UDT0 ; 
 int /*<<< orphan*/  R92C_DRVERLYINT ; 
 int /*<<< orphan*/  R92C_TBTT_PROHIBIT ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtwn_init_beacon_reg(struct rtwn_softc *sc)
{
	rtwn_write_1(sc, R92C_BCN_CTRL(0), R92C_BCN_CTRL_DIS_TSF_UDT0);
	rtwn_write_1(sc, R92C_BCN_CTRL(1), R92C_BCN_CTRL_DIS_TSF_UDT0);
	rtwn_write_2(sc, R92C_TBTT_PROHIBIT, 0x6404);
	rtwn_write_1(sc, R92C_DRVERLYINT, 0x05);
	rtwn_write_1(sc, R92C_BCNDMATIM, 0x02);
	rtwn_write_2(sc, R92C_BCNTCFG, 0x660f);
}