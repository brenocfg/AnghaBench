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
struct scatterlist {int dummy; } ;
struct ib_mr {unsigned int page_size; TYPE_1__* device; } ;
struct TYPE_2__ {int (* map_mr_sg ) (struct ib_mr*,struct scatterlist*,int,unsigned int*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_mr*,struct scatterlist*,int,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

int ib_map_mr_sg(struct ib_mr *mr, struct scatterlist *sg, int sg_nents,
		 unsigned int *sg_offset, unsigned int page_size)
{
	if (unlikely(!mr->device->map_mr_sg))
		return -ENOSYS;

	mr->page_size = page_size;

	return mr->device->map_mr_sg(mr, sg, sg_nents, sg_offset);
}