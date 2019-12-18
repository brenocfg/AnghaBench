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
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cppi41_dd {TYPE_1__ ddev; int /*<<< orphan*/  pending; } ;
struct cppi41_channel {struct cppi41_dd* cdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 struct cppi41_channel* to_cpp41_chan (struct dma_chan*) ; 

__attribute__((used)) static void cppi41_dma_free_chan_resources(struct dma_chan *chan)
{
	struct cppi41_channel *c = to_cpp41_chan(chan);
	struct cppi41_dd *cdd = c->cdd;
	int error;

	error = pm_runtime_get_sync(cdd->ddev.dev);
	if (error < 0) {
		pm_runtime_put_noidle(cdd->ddev.dev);

		return;
	}

	WARN_ON(!list_empty(&cdd->pending));

	pm_runtime_mark_last_busy(cdd->ddev.dev);
	pm_runtime_put_autosuspend(cdd->ddev.dev);
}