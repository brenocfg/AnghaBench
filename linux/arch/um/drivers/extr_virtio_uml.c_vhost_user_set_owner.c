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
 int /*<<< orphan*/  VHOST_USER_SET_OWNER ; 
 int vhost_user_send_no_payload (struct virtio_uml_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhost_user_set_owner(struct virtio_uml_device *vu_dev)
{
	return vhost_user_send_no_payload(vu_dev, false, VHOST_USER_SET_OWNER);
}