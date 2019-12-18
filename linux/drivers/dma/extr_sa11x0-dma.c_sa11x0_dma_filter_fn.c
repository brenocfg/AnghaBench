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
struct sa11x0_dma_chan {int /*<<< orphan*/  name; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct sa11x0_dma_chan* to_sa11x0_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool sa11x0_dma_filter_fn(struct dma_chan *chan, void *param)
{
	struct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	const char *p = param;

	return !strcmp(c->name, p);
}