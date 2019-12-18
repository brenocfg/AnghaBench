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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ dir; int /*<<< orphan*/  dev_type; } ;
struct d40_chan {TYPE_1__ dma_cfg; } ;
typedef  enum d40_events { ____Placeholder_d40_events } d40_events ;

/* Variables and functions */
 int /*<<< orphan*/  D40_CHAN_REG_SDLNK ; 
 int /*<<< orphan*/  D40_CHAN_REG_SSLNK ; 
 int /*<<< orphan*/  D40_TYPE_TO_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_DEV_TO_DEV ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  __d40_config_set_event (struct d40_chan*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d40_config_set_event(struct d40_chan *d40c,
				 enum d40_events event_type)
{
	u32 event = D40_TYPE_TO_EVENT(d40c->dma_cfg.dev_type);

	/* Enable event line connected to device (or memcpy) */
	if ((d40c->dma_cfg.dir == DMA_DEV_TO_MEM) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_config_set_event(d40c, event_type, event,
				       D40_CHAN_REG_SSLNK);

	if (d40c->dma_cfg.dir !=  DMA_DEV_TO_MEM)
		__d40_config_set_event(d40c, event_type, event,
				       D40_CHAN_REG_SDLNK);
}