#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__ kobj; void* owner; } ;
struct ib_umad_port {int dev_num; int port_num; TYPE_2__ cdev; TYPE_2__ sm_cdev; void* sm_dev; void* dev; int /*<<< orphan*/  file_list; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  sm_sem; struct ib_device* ib_dev; } ;
struct ib_umad_device {int /*<<< orphan*/  kobj; } ;
struct ib_device {int /*<<< orphan*/  dma_device; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int IB_UMAD_MAX_PORTS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 void* THIS_MODULE ; 
 scalar_t__ base_dev ; 
 scalar_t__ cdev_add (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_attr_port ; 
 int /*<<< orphan*/  dev_map ; 
 void* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_umad_port*,char*,int) ; 
 scalar_t__ device_create_file (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_overflow_devnum (struct ib_device*) ; 
 int /*<<< orphan*/  kobject_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ overflow_maj ; 
 int /*<<< orphan*/  overflow_map ; 
 int /*<<< orphan*/  port_lock ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umad_class ; 
 int /*<<< orphan*/  umad_fops ; 
 int /*<<< orphan*/  umad_sm_fops ; 

__attribute__((used)) static int ib_umad_init_port(struct ib_device *device, int port_num,
			     struct ib_umad_device *umad_dev,
			     struct ib_umad_port *port)
{
	int devnum;
	dev_t base;

	spin_lock(&port_lock);
	devnum = find_first_zero_bit(dev_map, IB_UMAD_MAX_PORTS);
	if (devnum >= IB_UMAD_MAX_PORTS) {
		spin_unlock(&port_lock);
		devnum = find_overflow_devnum(device);
		if (devnum < 0)
			return -1;

		spin_lock(&port_lock);
		port->dev_num = devnum + IB_UMAD_MAX_PORTS;
		base = devnum + overflow_maj;
		set_bit(devnum, overflow_map);
	} else {
		port->dev_num = devnum;
		base = devnum + base_dev;
		set_bit(devnum, dev_map);
	}
	spin_unlock(&port_lock);

	port->ib_dev   = device;
	port->port_num = port_num;
	sema_init(&port->sm_sem, 1);
	mutex_init(&port->file_mutex);
	INIT_LIST_HEAD(&port->file_list);

	cdev_init(&port->cdev, &umad_fops);
	port->cdev.owner = THIS_MODULE;
	port->cdev.kobj.parent = &umad_dev->kobj;
	kobject_set_name(&port->cdev.kobj, "umad%d", port->dev_num);
	if (cdev_add(&port->cdev, base, 1))
		goto err_cdev;

	port->dev = device_create(umad_class, device->dma_device,
				  port->cdev.dev, port,
				  "umad%d", port->dev_num);
	if (IS_ERR(port->dev))
		goto err_cdev;

	if (device_create_file(port->dev, &dev_attr_ibdev))
		goto err_dev;
	if (device_create_file(port->dev, &dev_attr_port))
		goto err_dev;

	base += IB_UMAD_MAX_PORTS;
	cdev_init(&port->sm_cdev, &umad_sm_fops);
	port->sm_cdev.owner = THIS_MODULE;
	port->sm_cdev.kobj.parent = &umad_dev->kobj;
	kobject_set_name(&port->sm_cdev.kobj, "issm%d", port->dev_num);
	if (cdev_add(&port->sm_cdev, base, 1))
		goto err_sm_cdev;

	port->sm_dev = device_create(umad_class, device->dma_device,
				     port->sm_cdev.dev, port,
				     "issm%d", port->dev_num);
	if (IS_ERR(port->sm_dev))
		goto err_sm_cdev;

	if (device_create_file(port->sm_dev, &dev_attr_ibdev))
		goto err_sm_dev;
	if (device_create_file(port->sm_dev, &dev_attr_port))
		goto err_sm_dev;

	return 0;

err_sm_dev:
	device_destroy(umad_class, port->sm_cdev.dev);

err_sm_cdev:
	cdev_del(&port->sm_cdev);

err_dev:
	device_destroy(umad_class, port->cdev.dev);

err_cdev:
	cdev_del(&port->cdev);
	if (port->dev_num < IB_UMAD_MAX_PORTS)
		clear_bit(devnum, dev_map);
	else
		clear_bit(devnum, overflow_map);

	return -1;
}