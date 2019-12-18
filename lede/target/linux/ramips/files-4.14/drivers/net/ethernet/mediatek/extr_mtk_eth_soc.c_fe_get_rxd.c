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
struct fe_rx_dma {int /*<<< orphan*/  rxd4; int /*<<< orphan*/  rxd3; int /*<<< orphan*/  rxd2; int /*<<< orphan*/  rxd1; } ;

/* Variables and functions */

__attribute__((used)) static inline void fe_get_rxd(struct fe_rx_dma *rxd, struct fe_rx_dma *dma_rxd)
{
	rxd->rxd1 = dma_rxd->rxd1;
	rxd->rxd2 = dma_rxd->rxd2;
	rxd->rxd3 = dma_rxd->rxd3;
	rxd->rxd4 = dma_rxd->rxd4;
}