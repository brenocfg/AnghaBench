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
struct r92c_rx_stat {int /*<<< orphan*/  rxdw3; } ;

/* Variables and functions */
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R88E_RXDW3_RPT ; 
#define  R88E_RXDW3_RPT_HIS 131 
#define  R88E_RXDW3_RPT_RX 130 
#define  R88E_RXDW3_RPT_TX1 129 
#define  R88E_RXDW3_RPT_TX2 128 
 int RTWN_RX_DATA ; 
 int RTWN_RX_OTHER ; 
 int RTWN_RX_TX_REPORT ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

int
r88e_classify_intr(struct rtwn_softc *sc, void *buf, int len)
{
	struct r92c_rx_stat *stat = buf;
	int report_sel = MS(le32toh(stat->rxdw3), R88E_RXDW3_RPT);

	switch (report_sel) {
	case R88E_RXDW3_RPT_RX:
		return (RTWN_RX_DATA);
	case R88E_RXDW3_RPT_TX1:	/* per-packet Tx report */
	case R88E_RXDW3_RPT_TX2:	/* periodical Tx report */
		return (RTWN_RX_TX_REPORT);
	case R88E_RXDW3_RPT_HIS:
		return (RTWN_RX_OTHER);
	default:			/* shut up the compiler */
		return (RTWN_RX_DATA);
	}
}