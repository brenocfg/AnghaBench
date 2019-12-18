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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct of_dma {TYPE_1__* dma_router; struct dma_chan* (* of_dma_xlate ) (struct of_phandle_args*,struct of_dma*) ;void* (* of_dma_route_allocate ) (struct of_phandle_args*,struct of_dma*) ;} ;
struct dma_chan {void* route_data; TYPE_1__* router; } ;
typedef  int /*<<< orphan*/  dma_spec_target ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* route_free ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  memcpy (struct of_phandle_args*,struct of_phandle_args*,int) ; 
 struct of_dma* of_dma_find_controller (struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 void* stub1 (struct of_phandle_args*,struct of_dma*) ; 
 struct dma_chan* stub2 (struct of_phandle_args*,struct of_dma*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct dma_chan *of_dma_router_xlate(struct of_phandle_args *dma_spec,
					    struct of_dma *ofdma)
{
	struct dma_chan		*chan;
	struct of_dma		*ofdma_target;
	struct of_phandle_args	dma_spec_target;
	void			*route_data;

	/* translate the request for the real DMA controller */
	memcpy(&dma_spec_target, dma_spec, sizeof(dma_spec_target));
	route_data = ofdma->of_dma_route_allocate(&dma_spec_target, ofdma);
	if (IS_ERR(route_data))
		return NULL;

	ofdma_target = of_dma_find_controller(&dma_spec_target);
	if (!ofdma_target)
		return NULL;

	chan = ofdma_target->of_dma_xlate(&dma_spec_target, ofdma_target);
	if (chan) {
		chan->router = ofdma->dma_router;
		chan->route_data = route_data;
	} else {
		ofdma->dma_router->route_free(ofdma->dma_router->dev,
					      route_data);
	}

	/*
	 * Need to put the node back since the ofdma->of_dma_route_allocate
	 * has taken it for generating the new, translated dma_spec
	 */
	of_node_put(dma_spec_target.np);
	return chan;
}