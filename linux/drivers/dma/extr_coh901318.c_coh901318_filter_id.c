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
struct TYPE_2__ {unsigned long id; } ;

/* Variables and functions */
 TYPE_1__* to_coh901318_chan (struct dma_chan*) ; 

bool coh901318_filter_id(struct dma_chan *chan, void *chan_id)
{
	unsigned long ch_nr = (unsigned long) chan_id;

	if (ch_nr == to_coh901318_chan(chan)->id)
		return true;

	return false;
}