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
 int /*<<< orphan*/  ep93xx_dma_advance_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ep93xx_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void ep93xx_dma_issue_pending(struct dma_chan *chan)
{
	ep93xx_dma_advance_work(to_ep93xx_dma_chan(chan));
}