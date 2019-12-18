#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base_phys_addr; } ;
typedef  TYPE_1__ ips_copper_queue_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void ips_copperhead_queue_callback(void *queueptr, bus_dma_segment_t *segments,int segnum, int error)
{
	ips_copper_queue_t *queue = queueptr;
	if(error){
		return;
	}
	queue->base_phys_addr = segments[0].ds_addr;
}