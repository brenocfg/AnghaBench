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
struct idma64_chan {int /*<<< orphan*/ * pool; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  to_virt_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_free_chan_resources(struct dma_chan *chan)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);

	vchan_free_chan_resources(to_virt_chan(chan));
	dma_pool_destroy(idma64c->pool);
	idma64c->pool = NULL;
}