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
struct sdma_engine {scalar_t__ regs; } ;
struct sdma_channel {int channel; struct sdma_engine* sdma; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SDMA_H_DSPOVR ; 
 scalar_t__ SDMA_H_EVTOVR ; 
 scalar_t__ SDMA_H_HOSTOVR ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int sdma_config_ownership(struct sdma_channel *sdmac,
		bool event_override, bool mcu_override, bool dsp_override)
{
	struct sdma_engine *sdma = sdmac->sdma;
	int channel = sdmac->channel;
	unsigned long evt, mcu, dsp;

	if (event_override && mcu_override && dsp_override)
		return -EINVAL;

	evt = readl_relaxed(sdma->regs + SDMA_H_EVTOVR);
	mcu = readl_relaxed(sdma->regs + SDMA_H_HOSTOVR);
	dsp = readl_relaxed(sdma->regs + SDMA_H_DSPOVR);

	if (dsp_override)
		__clear_bit(channel, &dsp);
	else
		__set_bit(channel, &dsp);

	if (event_override)
		__clear_bit(channel, &evt);
	else
		__set_bit(channel, &evt);

	if (mcu_override)
		__clear_bit(channel, &mcu);
	else
		__set_bit(channel, &mcu);

	writel_relaxed(evt, sdma->regs + SDMA_H_EVTOVR);
	writel_relaxed(mcu, sdma->regs + SDMA_H_HOSTOVR);
	writel_relaxed(dsp, sdma->regs + SDMA_H_DSPOVR);

	return 0;
}