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
typedef  int uint32_t ;
struct bhnd_dma_translation {int addr_mask; int base_addr; int addrext_mask; } ;
struct bwn_dma {int addrext_shift; struct bhnd_dma_translation translation; } ;
struct TYPE_2__ {struct bwn_dma dma; } ;
struct bwn_mac {TYPE_1__ mac_method; } ;
struct bwn_dmadesc64 {int dummy; } ;
struct bwn_dmadesc32 {int dummy; } ;
struct bwn_dma_ring {int dr_ring_dmabase; int dr_curslot; scalar_t__ dr_type; int dr_usedslot; int dr_numslots; int dr_frameoffset; scalar_t__ dr_tx; struct bwn_mac* dr_mac; } ;
typedef  int bhnd_addr_t ;

/* Variables and functions */
 scalar_t__ BHND_DMA_ADDR_64BIT ; 
 int BWN_DMA32_RXADDREXT_MASK ; 
 int BWN_DMA32_RXADDREXT_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA32_RXCTL ; 
 int BWN_DMA32_RXENABLE ; 
 int BWN_DMA32_RXFROFF_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA32_RXINDEX ; 
 int BWN_DMA32_RXPARITY_DISABLE ; 
 int /*<<< orphan*/  BWN_DMA32_RXRING ; 
 int BWN_DMA32_TXADDREXT_MASK ; 
 int BWN_DMA32_TXADDREXT_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA32_TXCTL ; 
 int BWN_DMA32_TXENABLE ; 
 int BWN_DMA32_TXPARITY_DISABLE ; 
 int /*<<< orphan*/  BWN_DMA32_TXRING ; 
 int BWN_DMA64_RXADDREXT_MASK ; 
 int BWN_DMA64_RXADDREXT_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA64_RXCTL ; 
 int BWN_DMA64_RXENABLE ; 
 int BWN_DMA64_RXFROFF_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA64_RXINDEX ; 
 int BWN_DMA64_RXPARITY_DISABLE ; 
 int /*<<< orphan*/  BWN_DMA64_RXRINGHI ; 
 int /*<<< orphan*/  BWN_DMA64_RXRINGLO ; 
 int BWN_DMA64_TXADDREXT_MASK ; 
 int BWN_DMA64_TXADDREXT_SHIFT ; 
 int /*<<< orphan*/  BWN_DMA64_TXCTL ; 
 int BWN_DMA64_TXENABLE ; 
 int BWN_DMA64_TXPARITY_DISABLE ; 
 int /*<<< orphan*/  BWN_DMA64_TXRINGHI ; 
 int /*<<< orphan*/  BWN_DMA64_TXRINGLO ; 
 int /*<<< orphan*/  BWN_DMA_WRITE (struct bwn_dma_ring*,int /*<<< orphan*/ ,int) ; 
 int UINT32_MAX ; 

__attribute__((used)) static void
bwn_dma_setup(struct bwn_dma_ring *dr)
{
	struct bwn_mac			*mac;
	struct bwn_dma			*dma;
	struct bhnd_dma_translation	*dt;
	bhnd_addr_t			 addr, paddr;
	uint32_t			 addrhi, addrlo, addrext, value;

	mac = dr->dr_mac;
	dma = &mac->mac_method.dma;
	dt = &dma->translation;

	paddr = dr->dr_ring_dmabase;
	addr = (paddr & dt->addr_mask) | dt->base_addr;
	addrhi = (addr >> 32);
	addrlo = (addr & UINT32_MAX);
	addrext = ((paddr & dt->addrext_mask) >> dma->addrext_shift);

	if (dr->dr_tx) {
		dr->dr_curslot = -1;

		if (dr->dr_type == BHND_DMA_ADDR_64BIT) {
			value = BWN_DMA64_TXENABLE;
			value |= BWN_DMA64_TXPARITY_DISABLE;
			value |= (addrext << BWN_DMA64_TXADDREXT_SHIFT)
			    & BWN_DMA64_TXADDREXT_MASK;
			BWN_DMA_WRITE(dr, BWN_DMA64_TXCTL, value);
			BWN_DMA_WRITE(dr, BWN_DMA64_TXRINGLO, addrlo);
			BWN_DMA_WRITE(dr, BWN_DMA64_TXRINGHI, addrhi);
		} else {
			value = BWN_DMA32_TXENABLE;
			value |= BWN_DMA32_TXPARITY_DISABLE;
			value |= (addrext << BWN_DMA32_TXADDREXT_SHIFT)
			    & BWN_DMA32_TXADDREXT_MASK;
			BWN_DMA_WRITE(dr, BWN_DMA32_TXCTL, value);
			BWN_DMA_WRITE(dr, BWN_DMA32_TXRING, addrlo);
		}
		return;
	}

	/*
	 * set for RX
	 */
	dr->dr_usedslot = dr->dr_numslots;

	if (dr->dr_type == BHND_DMA_ADDR_64BIT) {
		value = (dr->dr_frameoffset << BWN_DMA64_RXFROFF_SHIFT);
		value |= BWN_DMA64_RXENABLE;
		value |= BWN_DMA64_RXPARITY_DISABLE;
		value |= (addrext << BWN_DMA64_RXADDREXT_SHIFT)
		    & BWN_DMA64_RXADDREXT_MASK;
		BWN_DMA_WRITE(dr, BWN_DMA64_RXCTL, value);
		BWN_DMA_WRITE(dr, BWN_DMA64_RXRINGLO, addrlo);
		BWN_DMA_WRITE(dr, BWN_DMA64_RXRINGHI, addrhi);
		BWN_DMA_WRITE(dr, BWN_DMA64_RXINDEX, dr->dr_numslots *
		    sizeof(struct bwn_dmadesc64));
	} else {
		value = (dr->dr_frameoffset << BWN_DMA32_RXFROFF_SHIFT);
		value |= BWN_DMA32_RXENABLE;
		value |= BWN_DMA32_RXPARITY_DISABLE;
		value |= (addrext << BWN_DMA32_RXADDREXT_SHIFT)
		    & BWN_DMA32_RXADDREXT_MASK;
		BWN_DMA_WRITE(dr, BWN_DMA32_RXCTL, value);
		BWN_DMA_WRITE(dr, BWN_DMA32_RXRING, addrlo);
		BWN_DMA_WRITE(dr, BWN_DMA32_RXINDEX, dr->dr_numslots *
		    sizeof(struct bwn_dmadesc32));
	}
}