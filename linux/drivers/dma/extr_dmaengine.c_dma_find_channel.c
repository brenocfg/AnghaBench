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
typedef  enum dma_transaction_type { ____Placeholder_dma_transaction_type } dma_transaction_type ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 TYPE_1__** channel_table ; 
 struct dma_chan* this_cpu_read (int /*<<< orphan*/ ) ; 

struct dma_chan *dma_find_channel(enum dma_transaction_type tx_type)
{
	return this_cpu_read(channel_table[tx_type]->chan);
}