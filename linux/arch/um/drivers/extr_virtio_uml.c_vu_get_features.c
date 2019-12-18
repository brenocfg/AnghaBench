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
typedef  int /*<<< orphan*/  u64 ;
struct virtio_uml_device {int /*<<< orphan*/  features; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 struct virtio_uml_device* to_virtio_uml_device (struct virtio_device*) ; 

__attribute__((used)) static u64 vu_get_features(struct virtio_device *vdev)
{
	struct virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	return vu_dev->features;
}