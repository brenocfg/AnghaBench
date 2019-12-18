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
typedef  int uint32_t ;
struct camdd_dev {int cur_active_io; int num_run_queue; scalar_t__ num_peer_work_queue; scalar_t__ num_peer_done_queue; int blocksize; int peer_bytes_queued; } ;

/* Variables and functions */

void
camdd_get_depth(struct camdd_dev *dev, uint32_t *our_depth,
		uint32_t *peer_depth, uint32_t *our_bytes, uint32_t *peer_bytes)
{
	*our_depth = dev->cur_active_io + dev->num_run_queue;
	if (dev->num_peer_work_queue >
	    dev->num_peer_done_queue)
		*peer_depth = dev->num_peer_work_queue -
			      dev->num_peer_done_queue;
	else
		*peer_depth = 0;
	*our_bytes = *our_depth * dev->blocksize;
	*peer_bytes = dev->peer_bytes_queued;
}