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
typedef  int u8 ;
struct vio_version {int dummy; } ;
struct vio_driver_state {char* name; int dev_class; int ver_table_entries; int /*<<< orphan*/  timer; struct vio_driver_ops* ops; struct vio_version* ver_table; struct vio_dev* vdev; int /*<<< orphan*/  lock; } ;
struct vio_driver_ops {int /*<<< orphan*/  handshake_complete; int /*<<< orphan*/  handle_attr; int /*<<< orphan*/  send_attr; } ;
struct vio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VDEV_CONSOLE_CON 132 
#define  VDEV_DISK 131 
#define  VDEV_DISK_SERVER 130 
#define  VDEV_NETWORK 129 
#define  VDEV_NETWORK_SWITCH 128 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_port_timer ; 

int vio_driver_init(struct vio_driver_state *vio, struct vio_dev *vdev,
		    u8 dev_class, struct vio_version *ver_table,
		    int ver_table_size, struct vio_driver_ops *ops,
		    char *name)
{
	switch (dev_class) {
	case VDEV_NETWORK:
	case VDEV_NETWORK_SWITCH:
	case VDEV_DISK:
	case VDEV_DISK_SERVER:
	case VDEV_CONSOLE_CON:
		break;

	default:
		return -EINVAL;
	}

	if (dev_class == VDEV_NETWORK ||
	    dev_class == VDEV_NETWORK_SWITCH ||
	    dev_class == VDEV_DISK ||
	    dev_class == VDEV_DISK_SERVER) {
		if (!ops || !ops->send_attr || !ops->handle_attr ||
		    !ops->handshake_complete)
			return -EINVAL;
	}

	if (!ver_table || ver_table_size < 0)
		return -EINVAL;

	if (!name)
		return -EINVAL;

	spin_lock_init(&vio->lock);

	vio->name = name;

	vio->dev_class = dev_class;
	vio->vdev = vdev;

	vio->ver_table = ver_table;
	vio->ver_table_entries = ver_table_size;

	vio->ops = ops;

	timer_setup(&vio->timer, vio_port_timer, 0);

	return 0;
}