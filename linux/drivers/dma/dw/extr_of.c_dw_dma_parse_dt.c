#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dw_dma_platform_data {int nr_masters; int nr_channels; unsigned char chan_allocation_order; int chan_priority; int block_size; int* data_width; int* multi_block; int protctl; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CHAN_PROTCTL_MASK ; 
 int DW_DMA_MAX_NR_CHANNELS ; 
 int DW_DMA_MAX_NR_MASTERS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct dw_dma_platform_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

struct dw_dma_platform_data *dw_dma_parse_dt(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct dw_dma_platform_data *pdata;
	u32 tmp, arr[DW_DMA_MAX_NR_MASTERS], mb[DW_DMA_MAX_NR_CHANNELS];
	u32 nr_masters;
	u32 nr_channels;

	if (!np) {
		dev_err(&pdev->dev, "Missing DT data\n");
		return NULL;
	}

	if (of_property_read_u32(np, "dma-masters", &nr_masters))
		return NULL;
	if (nr_masters < 1 || nr_masters > DW_DMA_MAX_NR_MASTERS)
		return NULL;

	if (of_property_read_u32(np, "dma-channels", &nr_channels))
		return NULL;
	if (nr_channels > DW_DMA_MAX_NR_CHANNELS)
		return NULL;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	pdata->nr_masters = nr_masters;
	pdata->nr_channels = nr_channels;

	if (!of_property_read_u32(np, "chan_allocation_order", &tmp))
		pdata->chan_allocation_order = (unsigned char)tmp;

	if (!of_property_read_u32(np, "chan_priority", &tmp))
		pdata->chan_priority = tmp;

	if (!of_property_read_u32(np, "block_size", &tmp))
		pdata->block_size = tmp;

	if (!of_property_read_u32_array(np, "data-width", arr, nr_masters)) {
		for (tmp = 0; tmp < nr_masters; tmp++)
			pdata->data_width[tmp] = arr[tmp];
	} else if (!of_property_read_u32_array(np, "data_width", arr, nr_masters)) {
		for (tmp = 0; tmp < nr_masters; tmp++)
			pdata->data_width[tmp] = BIT(arr[tmp] & 0x07);
	}

	if (!of_property_read_u32_array(np, "multi-block", mb, nr_channels)) {
		for (tmp = 0; tmp < nr_channels; tmp++)
			pdata->multi_block[tmp] = mb[tmp];
	} else {
		for (tmp = 0; tmp < nr_channels; tmp++)
			pdata->multi_block[tmp] = 1;
	}

	if (!of_property_read_u32(np, "snps,dma-protection-control", &tmp)) {
		if (tmp > CHAN_PROTCTL_MASK)
			return NULL;
		pdata->protctl = tmp;
	}

	return pdata;
}