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
struct r92c_tx_desc {int flags0; int /*<<< orphan*/  txdw5; int /*<<< orphan*/  txdw4; int /*<<< orphan*/  txdw1; } ;

/* Variables and functions */
 int R92C_FLAGS0_BMCAST ; 
 int R92C_FLAGS0_FSG ; 
 int R92C_FLAGS0_LSG ; 
 int R92C_RAID_11B ; 
 int /*<<< orphan*/  R92C_TXDW1_QSEL ; 
 int R92C_TXDW1_QSEL_BEACON ; 
 int /*<<< orphan*/  R92C_TXDW1_RAID ; 
 int R92C_TXDW4_DRVRATE ; 
 int /*<<< orphan*/  R92C_TXDW4_PORT_ID ; 
 int /*<<< orphan*/  R92C_TXDW4_SEQ_SEL ; 
 int /*<<< orphan*/  R92C_TXDW5_DATARATE ; 
 int RTWN_RIDX_CCK1 ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  rtwn_r92c_tx_setup_macid (struct rtwn_softc*,void*,int) ; 

void
r92c_beacon_init(struct rtwn_softc *sc, void *buf, int id)
{
	struct r92c_tx_desc *txd = (struct r92c_tx_desc *)buf;

	/*
	 * NB: there is no need to setup HWSEQ_EN bit;
	 * QSEL_BEACON already implies it.
	 */
	txd->flags0 |= R92C_FLAGS0_BMCAST | R92C_FLAGS0_FSG | R92C_FLAGS0_LSG;
	txd->txdw1 |= htole32(
	    SM(R92C_TXDW1_QSEL, R92C_TXDW1_QSEL_BEACON) |
	    SM(R92C_TXDW1_RAID, R92C_RAID_11B));

	rtwn_r92c_tx_setup_macid(sc, buf, id);
	txd->txdw4 |= htole32(R92C_TXDW4_DRVRATE);
	txd->txdw4 |= htole32(SM(R92C_TXDW4_SEQ_SEL, id));
	txd->txdw4 |= htole32(SM(R92C_TXDW4_PORT_ID, id));
	txd->txdw5 |= htole32(SM(R92C_TXDW5_DATARATE, RTWN_RIDX_CCK1));
}