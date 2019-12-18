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
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxs_dma_disable_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  mxs_dma_reset_chan (struct dma_chan*) ; 

__attribute__((used)) static int mxs_dma_terminate_all(struct dma_chan *chan)
{
	mxs_dma_reset_chan(chan);
	mxs_dma_disable_chan(chan);

	return 0;
}