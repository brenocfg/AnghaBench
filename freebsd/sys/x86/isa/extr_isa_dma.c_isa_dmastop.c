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
 int /*<<< orphan*/  DMA1_SMSK ; 
 int /*<<< orphan*/  DMA2_SMSK ; 
 int dma_auto_mode ; 
 int dma_busy ; 
 int dma_inuse ; 
 int /*<<< orphan*/  isa_dma_lock ; 
 int isa_dmastatus_locked (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
isa_dmastop(int chan) 
{
	int status;

	mtx_lock(&isa_dma_lock);
	if ((dma_inuse & (1 << chan)) == 0)
		printf("isa_dmastop: channel %d not acquired\n", chan);  

	if (((dma_busy & (1 << chan)) == 0) &&
	    ((dma_auto_mode & (1 << chan)) == 0)) {
		printf("chan %d not busy\n", chan);
		mtx_unlock(&isa_dma_lock);
		return -2 ;
	}
    
	if ((chan & 4) == 0) {
		outb(DMA1_SMSK, (chan & 3) | 4 /* disable mask */);
	} else {
		outb(DMA2_SMSK, (chan & 3) | 4 /* disable mask */);
	}

	status = isa_dmastatus_locked(chan);

	mtx_unlock(&isa_dma_lock);

	return (status);
}