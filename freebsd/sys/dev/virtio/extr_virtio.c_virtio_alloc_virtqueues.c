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
struct vq_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int VIRTIO_BUS_ALLOC_VIRTQUEUES (int /*<<< orphan*/ ,int,int,struct vq_alloc_info*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
virtio_alloc_virtqueues(device_t dev, int flags, int nvqs,
    struct vq_alloc_info *info)
{

	return (VIRTIO_BUS_ALLOC_VIRTQUEUES(device_get_parent(dev), flags,
	    nvqs, info));
}