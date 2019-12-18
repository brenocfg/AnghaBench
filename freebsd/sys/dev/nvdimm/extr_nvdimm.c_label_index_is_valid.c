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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct nvdimm_label_index {scalar_t__ checksum; size_t this_offset; size_t this_size; size_t other_offset; int seq; scalar_t__ slot_cnt; int label_size; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVDIMM_INDEX_BLOCK_SIGNATURE ; 
 scalar_t__ fletcher64 (struct nvdimm_label_index*,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
label_index_is_valid(struct nvdimm_label_index *index, uint32_t max_labels,
    size_t size, size_t offset)
{
	uint64_t checksum;

	index = (struct nvdimm_label_index *)((uint8_t *)index + size * offset);
	if (strcmp(index->signature, NVDIMM_INDEX_BLOCK_SIGNATURE) != 0)
		return false;
	checksum = index->checksum;
	index->checksum = 0;
	if (checksum != fletcher64(index, size) ||
	    index->this_offset != size * offset || index->this_size != size ||
	    index->other_offset != size * (offset == 0 ? 1 : 0) ||
	    index->seq == 0 || index->seq > 3 || index->slot_cnt > max_labels ||
	    index->label_size != 1)
		return false;
	return true;
}