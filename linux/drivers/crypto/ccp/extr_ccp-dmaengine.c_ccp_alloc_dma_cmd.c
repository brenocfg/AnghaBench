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
struct ccp_dma_cmd {int dummy; } ;
struct ccp_dma_chan {TYPE_1__* ccp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_cmd_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct ccp_dma_cmd* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ccp_dma_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ccp_dma_cmd *ccp_alloc_dma_cmd(struct ccp_dma_chan *chan)
{
	struct ccp_dma_cmd *cmd;

	cmd = kmem_cache_alloc(chan->ccp->dma_cmd_cache, GFP_NOWAIT);
	if (cmd)
		memset(cmd, 0, sizeof(*cmd));

	return cmd;
}