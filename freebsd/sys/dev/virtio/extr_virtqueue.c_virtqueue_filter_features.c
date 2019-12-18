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
typedef  int uint64_t ;

/* Variables and functions */
 int VIRTIO_RING_F_EVENT_IDX ; 
 int VIRTIO_RING_F_INDIRECT_DESC ; 
 int VIRTIO_TRANSPORT_F_START ; 

uint64_t
virtqueue_filter_features(uint64_t features)
{
	uint64_t mask;

	mask = (1 << VIRTIO_TRANSPORT_F_START) - 1;
	mask |= VIRTIO_RING_F_INDIRECT_DESC;
	mask |= VIRTIO_RING_F_EVENT_IDX;

	return (features & mask);
}