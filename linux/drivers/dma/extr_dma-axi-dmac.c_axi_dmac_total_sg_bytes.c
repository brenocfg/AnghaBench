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
struct axi_dmac_sg {unsigned int x_len; unsigned int y_len; } ;
struct axi_dmac_chan {scalar_t__ hw_2d; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int axi_dmac_total_sg_bytes(struct axi_dmac_chan *chan,
	struct axi_dmac_sg *sg)
{
	if (chan->hw_2d)
		return sg->x_len * sg->y_len;
	else
		return sg->x_len;
}