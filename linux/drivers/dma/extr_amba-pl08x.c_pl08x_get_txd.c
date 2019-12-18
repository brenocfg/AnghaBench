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
struct pl08x_txd {int /*<<< orphan*/  dsg_list; } ;
struct pl08x_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pl08x_txd* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pl08x_txd *pl08x_get_txd(struct pl08x_dma_chan *plchan)
{
	struct pl08x_txd *txd = kzalloc(sizeof(*txd), GFP_NOWAIT);

	if (txd)
		INIT_LIST_HEAD(&txd->dsg_list);
	return txd;
}