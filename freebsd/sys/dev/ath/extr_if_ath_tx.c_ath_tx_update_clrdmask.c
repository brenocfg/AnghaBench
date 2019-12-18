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
struct ath_tid {int dummy; } ;
struct ath_softc {int dummy; } ;
struct ath_node {int clrdmask; } ;
struct TYPE_2__ {int /*<<< orphan*/  bfs_txflags; } ;
struct ath_buf {TYPE_1__ bf_state; int /*<<< orphan*/  bf_node; } ;

/* Variables and functions */
 struct ath_node* ATH_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_TXDESC_CLRDMASK ; 

__attribute__((used)) static void
ath_tx_update_clrdmask(struct ath_softc *sc, struct ath_tid *tid,
    struct ath_buf *bf)
{
	struct ath_node *an = ATH_NODE(bf->bf_node);

	ATH_TX_LOCK_ASSERT(sc);

	if (an->clrdmask == 1) {
		bf->bf_state.bfs_txflags |= HAL_TXDESC_CLRDMASK;
		an->clrdmask = 0;
	}
}