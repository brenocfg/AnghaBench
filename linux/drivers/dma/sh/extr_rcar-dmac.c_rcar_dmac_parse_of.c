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
struct rcar_dmac {int /*<<< orphan*/  n_channels; int /*<<< orphan*/  channels_mask; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCAR_DMAC_MAX_CHANNELS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_dmac_parse_of(struct device *dev, struct rcar_dmac *dmac)
{
	struct device_node *np = dev->of_node;
	int ret;

	ret = of_property_read_u32(np, "dma-channels", &dmac->n_channels);
	if (ret < 0) {
		dev_err(dev, "unable to read dma-channels property\n");
		return ret;
	}

	/* The hardware and driver don't support more than 32 bits in CHCLR */
	if (dmac->n_channels <= 0 ||
	    dmac->n_channels >= RCAR_DMAC_MAX_CHANNELS) {
		dev_err(dev, "invalid number of channels %u\n",
			dmac->n_channels);
		return -EINVAL;
	}

	dmac->channels_mask = GENMASK(dmac->n_channels - 1, 0);

	return 0;
}