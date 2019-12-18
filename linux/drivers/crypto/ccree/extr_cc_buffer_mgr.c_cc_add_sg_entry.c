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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct buffer_array {unsigned int num_of_buffers; unsigned int* nents; unsigned int* offset; unsigned int* total_data_len; int* is_last; scalar_t__** mlli_nents; int /*<<< orphan*/ * type; TYPE_1__* entry; } ;
struct TYPE_2__ {struct scatterlist* sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SGL_TYPE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,struct scatterlist*,unsigned int,int) ; 

__attribute__((used)) static void cc_add_sg_entry(struct device *dev, struct buffer_array *sgl_data,
			    unsigned int nents, struct scatterlist *sgl,
			    unsigned int data_len, unsigned int data_offset,
			    bool is_last_table, u32 *mlli_nents)
{
	unsigned int index = sgl_data->num_of_buffers;

	dev_dbg(dev, "index=%u nents=%u sgl=%pK data_len=0x%08X is_last=%d\n",
		index, nents, sgl, data_len, is_last_table);
	sgl_data->nents[index] = nents;
	sgl_data->entry[index].sgl = sgl;
	sgl_data->offset[index] = data_offset;
	sgl_data->total_data_len[index] = data_len;
	sgl_data->type[index] = DMA_SGL_TYPE;
	sgl_data->is_last[index] = is_last_table;
	sgl_data->mlli_nents[index] = mlli_nents;
	if (sgl_data->mlli_nents[index])
		*sgl_data->mlli_nents[index] = 0;
	sgl_data->num_of_buffers++;
}