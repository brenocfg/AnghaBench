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
struct virtio_uml_device {int dummy; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 struct virtio_uml_device* to_virtio_uml_device (struct virtio_device*) ; 
 int /*<<< orphan*/  vhost_user_set_config (struct virtio_uml_device*,unsigned int,void const*,unsigned int) ; 

__attribute__((used)) static void vu_set(struct virtio_device *vdev, unsigned offset,
		   const void *buf, unsigned len)
{
	struct virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	vhost_user_set_config(vu_dev, offset, buf, len);
}