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
struct fe_tx_dma {int /*<<< orphan*/  txd2; int /*<<< orphan*/  txd4; int /*<<< orphan*/  txd3; int /*<<< orphan*/  txd1; } ;

/* Variables and functions */

__attribute__((used)) static inline void fe_set_txd(struct fe_tx_dma *txd, struct fe_tx_dma *dma_txd)
{
	dma_txd->txd1 = txd->txd1;
	dma_txd->txd3 = txd->txd3;
	dma_txd->txd4 = txd->txd4;
	/* clean dma done flag last */
	dma_txd->txd2 = txd->txd2;
}