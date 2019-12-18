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

/* Variables and functions */
 int EBUSY ; 
 int VALID_DMA_MASK ; 
 int dma_auto_mode ; 
 int dma_inuse ; 
 int /*<<< orphan*/  isa_dma_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
isa_dma_acquire(int chan)
{
#ifdef DIAGNOSTIC
	if (chan & ~VALID_DMA_MASK)
		panic("isa_dma_acquire: channel out of range");
#endif

	mtx_lock(&isa_dma_lock);
	if (dma_inuse & (1 << chan)) {
		printf("isa_dma_acquire: channel %d already in use\n", chan);
		mtx_unlock(&isa_dma_lock);
		return (EBUSY);
	}
	dma_inuse |= (1 << chan);
	dma_auto_mode &= ~(1 << chan);
	mtx_unlock(&isa_dma_lock);

	return (0);
}