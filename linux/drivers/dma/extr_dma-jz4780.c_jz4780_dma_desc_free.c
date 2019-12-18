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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct jz4780_dma_desc {int /*<<< orphan*/  desc_phys; int /*<<< orphan*/  desc; } ;
struct jz4780_dma_chan {int /*<<< orphan*/  desc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct jz4780_dma_desc*) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (int /*<<< orphan*/ ) ; 
 struct jz4780_dma_desc* to_jz4780_dma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void jz4780_dma_desc_free(struct virt_dma_desc *vdesc)
{
	struct jz4780_dma_desc *desc = to_jz4780_dma_desc(vdesc);
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(vdesc->tx.chan);

	dma_pool_free(jzchan->desc_pool, desc->desc, desc->desc_phys);
	kfree(desc);
}