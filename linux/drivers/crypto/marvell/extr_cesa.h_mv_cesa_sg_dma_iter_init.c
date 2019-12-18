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
struct scatterlist {int dummy; } ;
struct mv_cesa_sg_dma_iter {int dir; struct scatterlist* sg; scalar_t__ offset; scalar_t__ op_offset; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */

__attribute__((used)) static inline void mv_cesa_sg_dma_iter_init(struct mv_cesa_sg_dma_iter *iter,
					    struct scatterlist *sg,
					    enum dma_data_direction dir)
{
	iter->op_offset = 0;
	iter->offset = 0;
	iter->sg = sg;
	iter->dir = dir;
}