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
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;
struct at_xdmac_chan {int /*<<< orphan*/  sconfig; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ at_xdmac_check_slave_config (struct dma_slave_config*) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct at_xdmac_chan* to_at_xdmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int at_xdmac_set_slave_config(struct dma_chan *chan,
				      struct dma_slave_config *sconfig)
{
	struct at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);

	if (at_xdmac_check_slave_config(sconfig)) {
		dev_err(chan2dev(chan), "invalid slave configuration\n");
		return -EINVAL;
	}

	memcpy(&atchan->sconfig, sconfig, sizeof(atchan->sconfig));

	return 0;
}