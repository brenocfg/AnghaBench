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
struct ioatdma_chan {int intr_coalesce; } ;
struct dma_chan {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int IOAT_INTRDELAY_MASK ; 
 int sscanf (char const*,char*,int*) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 

__attribute__((used)) static ssize_t intr_coalesce_store(struct dma_chan *c, const char *page,
size_t count)
{
	int intr_coalesce = 0;
	struct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	if (sscanf(page, "%du", &intr_coalesce) != -1) {
		if ((intr_coalesce < 0) ||
		    (intr_coalesce > IOAT_INTRDELAY_MASK))
			return -EINVAL;
		ioat_chan->intr_coalesce = intr_coalesce;
	}

	return count;
}