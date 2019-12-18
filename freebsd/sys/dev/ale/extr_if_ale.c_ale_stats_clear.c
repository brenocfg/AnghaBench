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
typedef  int /*<<< orphan*/  uint32_t ;
struct smb {int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_pkts_filtered; int /*<<< orphan*/  rx_frames; } ;
struct ale_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALE_RX_MIB_BASE ; 
 scalar_t__ ALE_TX_MIB_BASE ; 
 int /*<<< orphan*/  CSR_READ_4 (struct ale_softc*,scalar_t__) ; 

__attribute__((used)) static void
ale_stats_clear(struct ale_softc *sc)
{
	struct smb sb;
	uint32_t *reg;
	int i;

	for (reg = &sb.rx_frames, i = 0; reg <= &sb.rx_pkts_filtered; reg++) {
		CSR_READ_4(sc, ALE_RX_MIB_BASE + i);
		i += sizeof(uint32_t);
	}
	/* Read Tx statistics. */
	for (reg = &sb.tx_frames, i = 0; reg <= &sb.tx_mcast_bytes; reg++) {
		CSR_READ_4(sc, ALE_TX_MIB_BASE + i);
		i += sizeof(uint32_t);
	}
}