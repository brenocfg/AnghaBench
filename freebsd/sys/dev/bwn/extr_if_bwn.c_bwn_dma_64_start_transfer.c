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
struct bwn_dmadesc64 {int dummy; } ;
struct bwn_dma_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_DMA64_TXINDEX ; 
 int /*<<< orphan*/  BWN_DMA_WRITE (struct bwn_dma_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_dma_64_start_transfer(struct bwn_dma_ring *dr, int slot)
{

	BWN_DMA_WRITE(dr, BWN_DMA64_TXINDEX,
	    (uint32_t)(slot * sizeof(struct bwn_dmadesc64)));
}