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
struct vio_driver_state {int dev_class; int /*<<< orphan*/  _peer_sid; int /*<<< orphan*/  _local_sid; } ;

/* Variables and functions */
#define  VDEV_DISK 131 
#define  VDEV_DISK_SERVER 130 
#define  VDEV_NETWORK 129 
#define  VDEV_NETWORK_SWITCH 128 

u32 vio_send_sid(struct vio_driver_state *vio)
{
	switch (vio->dev_class) {
	case VDEV_NETWORK:
	case VDEV_NETWORK_SWITCH:
	case VDEV_DISK:
	default:
		return vio->_local_sid;

	case VDEV_DISK_SERVER:
		return vio->_peer_sid;
	}
}