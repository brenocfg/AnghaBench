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
struct bwn_dma_ring {scalar_t__ dr_type; int /*<<< orphan*/  dr_base; int /*<<< orphan*/  dr_mac; scalar_t__ dr_tx; } ;

/* Variables and functions */
 scalar_t__ BHND_DMA_ADDR_64BIT ; 
 int /*<<< orphan*/  BWN_DMA32_RXRING ; 
 int /*<<< orphan*/  BWN_DMA32_TXRING ; 
 int /*<<< orphan*/  BWN_DMA64_RXRINGHI ; 
 int /*<<< orphan*/  BWN_DMA64_RXRINGLO ; 
 int /*<<< orphan*/  BWN_DMA64_TXRINGHI ; 
 int /*<<< orphan*/  BWN_DMA64_TXRINGLO ; 
 int /*<<< orphan*/  BWN_DMA_WRITE (struct bwn_dma_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_dma_rx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bwn_dma_tx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bwn_dma_cleanup(struct bwn_dma_ring *dr)
{

	if (dr->dr_tx) {
		bwn_dma_tx_reset(dr->dr_mac, dr->dr_base, dr->dr_type);
		if (dr->dr_type == BHND_DMA_ADDR_64BIT) {
			BWN_DMA_WRITE(dr, BWN_DMA64_TXRINGLO, 0);
			BWN_DMA_WRITE(dr, BWN_DMA64_TXRINGHI, 0);
		} else
			BWN_DMA_WRITE(dr, BWN_DMA32_TXRING, 0);
	} else {
		bwn_dma_rx_reset(dr->dr_mac, dr->dr_base, dr->dr_type);
		if (dr->dr_type == BHND_DMA_ADDR_64BIT) {
			BWN_DMA_WRITE(dr, BWN_DMA64_RXRINGLO, 0);
			BWN_DMA_WRITE(dr, BWN_DMA64_RXRINGHI, 0);
		} else
			BWN_DMA_WRITE(dr, BWN_DMA32_RXRING, 0);
	}
}