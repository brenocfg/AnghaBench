#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pxad_param {int /*<<< orphan*/  prio; int /*<<< orphan*/  drcmr; } ;
struct pxad_chan {int /*<<< orphan*/  prio; int /*<<< orphan*/  drcmr; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 TYPE_3__ pxad_driver ; 
 struct pxad_chan* to_pxad_chan (struct dma_chan*) ; 

__attribute__((used)) static bool pxad_filter_fn(struct dma_chan *chan, void *param)
{
	struct pxad_chan *c = to_pxad_chan(chan);
	struct pxad_param *p = param;

	if (chan->device->dev->driver != &pxad_driver.driver)
		return false;

	c->drcmr = p->drcmr;
	c->prio = p->prio;

	return true;
}