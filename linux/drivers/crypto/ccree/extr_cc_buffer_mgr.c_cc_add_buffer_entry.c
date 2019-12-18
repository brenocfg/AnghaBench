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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct buffer_array {unsigned int num_of_buffers; int* nents; unsigned int* total_data_len; int* is_last; scalar_t__** mlli_nents; int /*<<< orphan*/ * type; scalar_t__* offset; TYPE_1__* entry; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFF_TYPE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void cc_add_buffer_entry(struct device *dev,
				struct buffer_array *sgl_data,
				dma_addr_t buffer_dma, unsigned int buffer_len,
				bool is_last_entry, u32 *mlli_nents)
{
	unsigned int index = sgl_data->num_of_buffers;

	dev_dbg(dev, "index=%u single_buff=%pad buffer_len=0x%08X is_last=%d\n",
		index, &buffer_dma, buffer_len, is_last_entry);
	sgl_data->nents[index] = 1;
	sgl_data->entry[index].buffer_dma = buffer_dma;
	sgl_data->offset[index] = 0;
	sgl_data->total_data_len[index] = buffer_len;
	sgl_data->type[index] = DMA_BUFF_TYPE;
	sgl_data->is_last[index] = is_last_entry;
	sgl_data->mlli_nents[index] = mlli_nents;
	if (sgl_data->mlli_nents[index])
		*sgl_data->mlli_nents[index] = 0;
	sgl_data->num_of_buffers++;
}