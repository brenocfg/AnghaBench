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
struct sdma_channel {int peripheral_type; scalar_t__ watermark_level; scalar_t__ per_address2; scalar_t__ per_addr; scalar_t__ per_address; scalar_t__ shp_addr; scalar_t__* event_mask; int /*<<< orphan*/  event_id0; scalar_t__ event_id1; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ IMX_DMATYPE_ASRC ; 
 scalar_t__ IMX_DMATYPE_ASRC_SP ; 
#define  IMX_DMATYPE_DSP 129 
#define  IMX_DMATYPE_MEMORY 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sdma_config_ownership (struct sdma_channel*,int,int,int) ; 
 int /*<<< orphan*/  sdma_disable_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  sdma_get_pc (struct sdma_channel*,int) ; 
 int sdma_load_context (struct sdma_channel*) ; 
 int /*<<< orphan*/  sdma_set_watermarklevel_for_p2p (struct sdma_channel*) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sdma_config_channel(struct dma_chan *chan)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);
	int ret;

	sdma_disable_channel(chan);

	sdmac->event_mask[0] = 0;
	sdmac->event_mask[1] = 0;
	sdmac->shp_addr = 0;
	sdmac->per_addr = 0;

	switch (sdmac->peripheral_type) {
	case IMX_DMATYPE_DSP:
		sdma_config_ownership(sdmac, false, true, true);
		break;
	case IMX_DMATYPE_MEMORY:
		sdma_config_ownership(sdmac, false, true, false);
		break;
	default:
		sdma_config_ownership(sdmac, true, true, false);
		break;
	}

	sdma_get_pc(sdmac, sdmac->peripheral_type);

	if ((sdmac->peripheral_type != IMX_DMATYPE_MEMORY) &&
			(sdmac->peripheral_type != IMX_DMATYPE_DSP)) {
		/* Handle multiple event channels differently */
		if (sdmac->event_id1) {
			if (sdmac->peripheral_type == IMX_DMATYPE_ASRC_SP ||
			    sdmac->peripheral_type == IMX_DMATYPE_ASRC)
				sdma_set_watermarklevel_for_p2p(sdmac);
		} else
			__set_bit(sdmac->event_id0, sdmac->event_mask);

		/* Address */
		sdmac->shp_addr = sdmac->per_address;
		sdmac->per_addr = sdmac->per_address2;
	} else {
		sdmac->watermark_level = 0; /* FIXME: M3_BASE_ADDRESS */
	}

	ret = sdma_load_context(sdmac);

	return ret;
}