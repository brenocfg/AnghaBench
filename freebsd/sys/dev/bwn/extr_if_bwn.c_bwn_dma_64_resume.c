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
struct bwn_dma_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_DMA64_TXCTL ; 
 int BWN_DMA64_TXSUSPEND ; 
 int BWN_DMA_READ (struct bwn_dma_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_DMA_WRITE (struct bwn_dma_ring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_dma_64_resume(struct bwn_dma_ring *dr)
{

	BWN_DMA_WRITE(dr, BWN_DMA64_TXCTL,
	    BWN_DMA_READ(dr, BWN_DMA64_TXCTL) & ~BWN_DMA64_TXSUSPEND);
}