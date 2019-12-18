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
typedef  scalar_t__ u32 ;
struct mdc_chan {int chan_nr; int /*<<< orphan*/  mdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdc_writel (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void mdc_chan_writel(struct mdc_chan *mchan, u32 val, u32 reg)
{
	mdc_writel(mchan->mdma, val, mchan->chan_nr * 0x040 + reg);
}