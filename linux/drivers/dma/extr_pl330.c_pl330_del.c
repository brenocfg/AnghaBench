#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct pl330_dmac {int mcbufsz; int /*<<< orphan*/  mcode_bus; int /*<<< orphan*/  mcode_cpu; TYPE_2__ pcfg; TYPE_1__ ddma; int /*<<< orphan*/  tasks; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_PRIVILEGED ; 
 int /*<<< orphan*/  UNINIT ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmac_free_threads (struct pl330_dmac*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pl330_del(struct pl330_dmac *pl330)
{
	pl330->state = UNINIT;

	tasklet_kill(&pl330->tasks);

	/* Free DMAC resources */
	dmac_free_threads(pl330);

	dma_free_attrs(pl330->ddma.dev,
		pl330->pcfg.num_chan * pl330->mcbufsz, pl330->mcode_cpu,
		pl330->mcode_bus, DMA_ATTR_PRIVILEGED);
}