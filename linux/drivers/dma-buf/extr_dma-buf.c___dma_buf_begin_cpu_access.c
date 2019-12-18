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
struct dma_resv {int dummy; } ;
struct dma_buf {struct dma_resv* resv; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 long dma_resv_wait_timeout_rcu (struct dma_resv*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dma_buf_begin_cpu_access(struct dma_buf *dmabuf,
				      enum dma_data_direction direction)
{
	bool write = (direction == DMA_BIDIRECTIONAL ||
		      direction == DMA_TO_DEVICE);
	struct dma_resv *resv = dmabuf->resv;
	long ret;

	/* Wait on any implicit rendering fences */
	ret = dma_resv_wait_timeout_rcu(resv, write, true,
						  MAX_SCHEDULE_TIMEOUT);
	if (ret < 0)
		return ret;

	return 0;
}