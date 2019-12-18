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
typedef  int u_long ;

/* Variables and functions */
 int DMA1_CHN (int) ; 
 int DMA1_FFC ; 
 int DMA2_CHN (int) ; 
 int DMA2_FFC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  disable_intr () ; 
 int dma_auto_mode ; 
 int dma_busy ; 
 int dma_inuse ; 
 int /*<<< orphan*/  enable_intr () ; 
 int inb (int) ; 
 int /*<<< orphan*/  isa_dma_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
isa_dmastatus_locked(int chan)
{
	u_long	cnt = 0;
	int	ffport, waport;
	u_long	low1, high1, low2, high2;

	mtx_assert(&isa_dma_lock, MA_OWNED);

	/* channel active? */
	if ((dma_inuse & (1 << chan)) == 0) {
		printf("isa_dmastatus: channel %d not active\n", chan);
		return(-1);
	}
	/* channel busy? */

	if (((dma_busy & (1 << chan)) == 0) &&
	    (dma_auto_mode & (1 << chan)) == 0 ) {
	    printf("chan %d not busy\n", chan);
	    return -2 ;
	}	
	if (chan < 4) {			/* low DMA controller */
		ffport = DMA1_FFC;
		waport = DMA1_CHN(chan) + 1;
	} else {			/* high DMA controller */
		ffport = DMA2_FFC;
		waport = DMA2_CHN(chan - 4) + 2;
	}

	disable_intr();			/* no interrupts Mr Jones! */
	outb(ffport, 0);		/* clear register LSB flipflop */
	low1 = inb(waport);
	high1 = inb(waport);
	outb(ffport, 0);		/* clear again */
	low2 = inb(waport);
	high2 = inb(waport);
	enable_intr();			/* enable interrupts again */

	/* 
	 * Now decide if a wrap has tried to skew our results.
	 * Note that after TC, the count will read 0xffff, while we want 
	 * to return zero, so we add and then mask to compensate.
	 */
	if (low1 >= low2) {
		cnt = (low1 + (high1 << 8) + 1) & 0xffff;
	} else {
		cnt = (low2 + (high2 << 8) + 1) & 0xffff;
	}

	if (chan >= 4)			/* high channels move words */
		cnt *= 2;
	return(cnt);
}