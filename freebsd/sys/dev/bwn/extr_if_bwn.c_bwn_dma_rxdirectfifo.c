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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bwn_mac {scalar_t__ mac_dmatype; } ;

/* Variables and functions */
 scalar_t__ BHND_DMA_ADDR_64BIT ; 
 scalar_t__ BWN_DMA32_RXCTL ; 
 int /*<<< orphan*/  BWN_DMA32_RXDIRECTFIFO ; 
 scalar_t__ BWN_DMA64_RXCTL ; 
 int /*<<< orphan*/  BWN_DMA64_RXDIRECTFIFO ; 
 int /*<<< orphan*/  BWN_READ_4 (struct bwn_mac*,scalar_t__) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bwn_dma_base (scalar_t__,int) ; 

__attribute__((used)) static void
bwn_dma_rxdirectfifo(struct bwn_mac *mac, int idx, uint8_t enable)
{
	uint32_t ctl;
	uint16_t base;

	base = bwn_dma_base(mac->mac_dmatype, idx);
	if (mac->mac_dmatype == BHND_DMA_ADDR_64BIT) {
		ctl = BWN_READ_4(mac, base + BWN_DMA64_RXCTL);
		ctl &= ~BWN_DMA64_RXDIRECTFIFO;
		if (enable)
			ctl |= BWN_DMA64_RXDIRECTFIFO;
		BWN_WRITE_4(mac, base + BWN_DMA64_RXCTL, ctl);
	} else {
		ctl = BWN_READ_4(mac, base + BWN_DMA32_RXCTL);
		ctl &= ~BWN_DMA32_RXDIRECTFIFO;
		if (enable)
			ctl |= BWN_DMA32_RXDIRECTFIFO;
		BWN_WRITE_4(mac, base + BWN_DMA32_RXCTL, ctl);
	}
}