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
struct hsu_dma_chan {int /*<<< orphan*/  config; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct hsu_dma_chan* to_hsu_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int hsu_dma_slave_config(struct dma_chan *chan,
				struct dma_slave_config *config)
{
	struct hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);

	memcpy(&hsuc->config, config, sizeof(hsuc->config));

	return 0;
}