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
struct txx9dmac_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CHAR ; 
 int /*<<< orphan*/  CNTR ; 
 int /*<<< orphan*/  DAIR ; 
 int /*<<< orphan*/  DAR ; 
 int /*<<< orphan*/  SAIR ; 
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  TXX9_DMA_CCR_CHRST ; 
 int /*<<< orphan*/  channel64_clear_CHAR (struct txx9dmac_chan*) ; 
 int /*<<< orphan*/  channel_writel (struct txx9dmac_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_writeq (struct txx9dmac_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dmac64 (struct txx9dmac_chan*) ; 

__attribute__((used)) static void txx9dmac_reset_chan(struct txx9dmac_chan *dc)
{
	channel_writel(dc, CCR, TXX9_DMA_CCR_CHRST);
	if (is_dmac64(dc)) {
		channel64_clear_CHAR(dc);
		channel_writeq(dc, SAR, 0);
		channel_writeq(dc, DAR, 0);
	} else {
		channel_writel(dc, CHAR, 0);
		channel_writel(dc, SAR, 0);
		channel_writel(dc, DAR, 0);
	}
	channel_writel(dc, CNTR, 0);
	channel_writel(dc, SAIR, 0);
	channel_writel(dc, DAIR, 0);
	channel_writel(dc, CCR, 0);
}