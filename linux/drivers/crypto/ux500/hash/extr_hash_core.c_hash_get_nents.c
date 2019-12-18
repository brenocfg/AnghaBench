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
struct scatterlist {scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HASH_DMA_ALIGN_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int hash_get_nents(struct scatterlist *sg, int size, bool *aligned)
{
	int nents = 0;
	bool aligned_data = true;

	while (size > 0 && sg) {
		nents++;
		size -= sg->length;

		/* hash_set_dma_transfer will align last nent */
		if ((aligned && !IS_ALIGNED(sg->offset, HASH_DMA_ALIGN_SIZE)) ||
		    (!IS_ALIGNED(sg->length, HASH_DMA_ALIGN_SIZE) && size > 0))
			aligned_data = false;

		sg = sg_next(sg);
	}

	if (aligned)
		*aligned = aligned_data;

	if (size != 0)
		return -EFAULT;

	return nents;
}