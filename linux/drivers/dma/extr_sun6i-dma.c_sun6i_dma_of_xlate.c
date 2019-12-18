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
typedef  scalar_t__ u8 ;
struct sun6i_vchan {scalar_t__ port; } ;
struct sun6i_dma_dev {scalar_t__ max_request; int /*<<< orphan*/  slave; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct of_dma {struct sun6i_dma_dev* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 struct sun6i_vchan* to_sun6i_vchan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *sun6i_dma_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct sun6i_dma_dev *sdev = ofdma->of_dma_data;
	struct sun6i_vchan *vchan;
	struct dma_chan *chan;
	u8 port = dma_spec->args[0];

	if (port > sdev->max_request)
		return NULL;

	chan = dma_get_any_slave_channel(&sdev->slave);
	if (!chan)
		return NULL;

	vchan = to_sun6i_vchan(chan);
	vchan->port = port;

	return chan;
}