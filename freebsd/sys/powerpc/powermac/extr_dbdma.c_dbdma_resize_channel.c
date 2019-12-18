#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dbdma_command {int dummy; } ;
struct TYPE_3__ {int sc_nslots; } ;
typedef  TYPE_1__ dbdma_channel_t ;

/* Variables and functions */
 int PAGE_SIZE ; 

int
dbdma_resize_channel(dbdma_channel_t *chan, int newslots)
{

	if (newslots > (PAGE_SIZE / sizeof(struct dbdma_command)))
		return (-1);
	
	chan->sc_nslots = newslots;
	return (0);
}