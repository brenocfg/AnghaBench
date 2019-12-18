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
typedef  int u32 ;
struct sh_dmae_chan {int /*<<< orphan*/  xmit_shift; } ;

/* Variables and functions */
 int DM_INC ; 
 int /*<<< orphan*/  LOG2_DEFAULT_XFER_SIZE ; 
 int RS_AUTO ; 
 int SM_INC ; 
 int /*<<< orphan*/  calc_xmit_shift (struct sh_dmae_chan*,int) ; 
 int /*<<< orphan*/  chcr_write (struct sh_dmae_chan*,int) ; 
 int log2size_to_chcr (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmae_init(struct sh_dmae_chan *sh_chan)
{
	/*
	 * Default configuration for dual address memory-memory transfer.
	 */
	u32 chcr = DM_INC | SM_INC | RS_AUTO | log2size_to_chcr(sh_chan,
						   LOG2_DEFAULT_XFER_SIZE);
	sh_chan->xmit_shift = calc_xmit_shift(sh_chan, chcr);
	chcr_write(sh_chan, chcr);
}