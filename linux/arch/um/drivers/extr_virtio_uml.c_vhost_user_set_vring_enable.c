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
typedef  int /*<<< orphan*/  u32 ;
struct virtio_uml_device {int features; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VHOST_USER_F_PROTOCOL_FEATURES ; 
 int /*<<< orphan*/  VHOST_USER_SET_VRING_ENABLE ; 
 int vhost_user_set_vring_state (struct virtio_uml_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vhost_user_set_vring_enable(struct virtio_uml_device *vu_dev,
				       u32 index, bool enable)
{
	if (!(vu_dev->features & BIT_ULL(VHOST_USER_F_PROTOCOL_FEATURES)))
		return 0;

	return vhost_user_set_vring_state(vu_dev, VHOST_USER_SET_VRING_ENABLE,
					  index, enable);
}