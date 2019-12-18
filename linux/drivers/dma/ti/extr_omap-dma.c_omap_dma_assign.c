#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_dmadev {struct omap_chan** lch_map; TYPE_1__* plat; scalar_t__ base; } ;
struct omap_chan {scalar_t__ channel_base; } ;
struct TYPE_2__ {unsigned int channel_stride; } ;

/* Variables and functions */

__attribute__((used)) static void omap_dma_assign(struct omap_dmadev *od, struct omap_chan *c,
	unsigned lch)
{
	c->channel_base = od->base + od->plat->channel_stride * lch;

	od->lch_map[lch] = c;
}