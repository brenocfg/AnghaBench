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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_chan*) ; 
 struct dma_chan* dma_request_chan (struct device*,char const*) ; 

struct dma_chan *dma_request_slave_channel(struct device *dev,
					   const char *name)
{
	struct dma_chan *ch = dma_request_chan(dev, name);
	if (IS_ERR(ch))
		return NULL;

	return ch;
}