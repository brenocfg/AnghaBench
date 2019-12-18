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
struct virtio_uml_device {int features; int protocol_features; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VHOST_USER_F_PROTOCOL_FEATURES ; 
 int /*<<< orphan*/  VHOST_USER_PROTOCOL_F_SLAVE_REQ ; 
 int VHOST_USER_SUPPORTED_PROTOCOL_F ; 
 int vhost_user_get_features (struct virtio_uml_device*,int*) ; 
 int vhost_user_get_protocol_features (struct virtio_uml_device*,int*) ; 
 int vhost_user_init_slave_req (struct virtio_uml_device*) ; 
 int vhost_user_set_owner (struct virtio_uml_device*) ; 
 int vhost_user_set_protocol_features (struct virtio_uml_device*,int) ; 

__attribute__((used)) static int vhost_user_init(struct virtio_uml_device *vu_dev)
{
	int rc = vhost_user_set_owner(vu_dev);

	if (rc)
		return rc;
	rc = vhost_user_get_features(vu_dev, &vu_dev->features);
	if (rc)
		return rc;

	if (vu_dev->features & BIT_ULL(VHOST_USER_F_PROTOCOL_FEATURES)) {
		rc = vhost_user_get_protocol_features(vu_dev,
				&vu_dev->protocol_features);
		if (rc)
			return rc;
		vu_dev->protocol_features &= VHOST_USER_SUPPORTED_PROTOCOL_F;
		rc = vhost_user_set_protocol_features(vu_dev,
				vu_dev->protocol_features);
		if (rc)
			return rc;
	}

	if (vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_SLAVE_REQ)) {
		rc = vhost_user_init_slave_req(vu_dev);
		if (rc)
			return rc;
	}

	return 0;
}