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
struct sdma_channel {int /*<<< orphan*/  status; TYPE_1__* desc; } ;
struct TYPE_4__ {int status; scalar_t__ count; } ;
struct sdma_buffer_descriptor {TYPE_2__ mode; } ;
struct TYPE_3__ {int num_bd; scalar_t__ chn_real_count; struct sdma_buffer_descriptor* bd; } ;

/* Variables and functions */
 int BD_DONE ; 
 int BD_RROR ; 
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int /*<<< orphan*/  DMA_ERROR ; 
 int EIO ; 

__attribute__((used)) static void mxc_sdma_handle_channel_normal(struct sdma_channel *data)
{
	struct sdma_channel *sdmac = (struct sdma_channel *) data;
	struct sdma_buffer_descriptor *bd;
	int i, error = 0;

	sdmac->desc->chn_real_count = 0;
	/*
	 * non loop mode. Iterate over all descriptors, collect
	 * errors and call callback function
	 */
	for (i = 0; i < sdmac->desc->num_bd; i++) {
		bd = &sdmac->desc->bd[i];

		 if (bd->mode.status & (BD_DONE | BD_RROR))
			error = -EIO;
		 sdmac->desc->chn_real_count += bd->mode.count;
	}

	if (error)
		sdmac->status = DMA_ERROR;
	else
		sdmac->status = DMA_COMPLETE;
}