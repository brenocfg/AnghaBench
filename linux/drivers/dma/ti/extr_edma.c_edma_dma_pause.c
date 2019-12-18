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
struct edma_chan {int /*<<< orphan*/  edesc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  edma_pause (struct edma_chan*) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 

__attribute__((used)) static int edma_dma_pause(struct dma_chan *chan)
{
	struct edma_chan *echan = to_edma_chan(chan);

	if (!echan->edesc)
		return -EINVAL;

	edma_pause(echan);
	return 0;
}