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

/* Variables and functions */
 int /*<<< orphan*/  VHOST_USER_SET_VRING_CALL ; 
 int vhost_user_set_vring_fd (struct virtio_uml_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vhost_user_set_vring_call(struct virtio_uml_device *vu_dev,
				     int index, int fd)
{
	return vhost_user_set_vring_fd(vu_dev, VHOST_USER_SET_VRING_CALL,
				       index, fd);
}