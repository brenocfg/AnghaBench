#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_abortcol; int /*<<< orphan*/  tx_latecol; int /*<<< orphan*/  tx_multicol; int /*<<< orphan*/  tx_singlecol; int /*<<< orphan*/  tx_excdefer; int /*<<< orphan*/  tx_defer; int /*<<< orphan*/  tx_ctrl; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_mcast; int /*<<< orphan*/  tx_bcast; } ;
typedef  TYPE_1__ ae_stats_t ;

/* Variables and functions */
 int AE_TXS_ABORTCOL ; 
 int AE_TXS_BCAST ; 
 int AE_TXS_CTRL ; 
 int AE_TXS_DEFER ; 
 int AE_TXS_EXCDEFER ; 
 int AE_TXS_LATECOL ; 
 int AE_TXS_MCAST ; 
 int AE_TXS_MULTICOL ; 
 int AE_TXS_PAUSE ; 
 int AE_TXS_SINGLECOL ; 
 int AE_TXS_UNDERRUN ; 

__attribute__((used)) static void
ae_update_stats_tx(uint16_t flags, ae_stats_t *stats)
{

	if ((flags & AE_TXS_BCAST) != 0)
		stats->tx_bcast++;
	if ((flags & AE_TXS_MCAST) != 0)
		stats->tx_mcast++;
	if ((flags & AE_TXS_PAUSE) != 0)
		stats->tx_pause++;
	if ((flags & AE_TXS_CTRL) != 0)
		stats->tx_ctrl++;
	if ((flags & AE_TXS_DEFER) != 0)
		stats->tx_defer++;
	if ((flags & AE_TXS_EXCDEFER) != 0)
		stats->tx_excdefer++;
	if ((flags & AE_TXS_SINGLECOL) != 0)
		stats->tx_singlecol++;
	if ((flags & AE_TXS_MULTICOL) != 0)
		stats->tx_multicol++;
	if ((flags & AE_TXS_LATECOL) != 0)
		stats->tx_latecol++;
	if ((flags & AE_TXS_ABORTCOL) != 0)
		stats->tx_abortcol++;
	if ((flags & AE_TXS_UNDERRUN) != 0)
		stats->tx_underrun++;
}