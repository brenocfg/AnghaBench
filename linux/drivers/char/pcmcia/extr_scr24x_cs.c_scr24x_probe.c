#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct scr24x_dev {scalar_t__ devno; TYPE_2__ c_dev; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; } ;
struct pcmcia_device {int config_flags; int /*<<< orphan*/  dev; TYPE_1__** resource; struct scr24x_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t PCMCIA_IOPORT_0 ; 
 scalar_t__ SCR24X_DEVS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  devm_ioport_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct scr24x_dev*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct scr24x_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  scr24x_class ; 
 int /*<<< orphan*/  scr24x_config_check ; 
 int /*<<< orphan*/  scr24x_devt ; 
 int /*<<< orphan*/  scr24x_fops ; 
 int /*<<< orphan*/  scr24x_minors ; 

__attribute__((used)) static int scr24x_probe(struct pcmcia_device *link)
{
	struct scr24x_dev *dev;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->devno = find_first_zero_bit(scr24x_minors, SCR24X_DEVS);
	if (dev->devno >= SCR24X_DEVS) {
		ret = -EBUSY;
		goto err;
	}

	mutex_init(&dev->lock);
	kref_init(&dev->refcnt);

	link->priv = dev;
	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, scr24x_config_check, NULL);
	if (ret < 0)
		goto err;

	dev->dev = &link->dev;
	dev->regs = devm_ioport_map(&link->dev,
				link->resource[PCMCIA_IOPORT_0]->start,
				resource_size(link->resource[PCMCIA_IOPORT_0]));
	if (!dev->regs) {
		ret = -EIO;
		goto err;
	}

	cdev_init(&dev->c_dev, &scr24x_fops);
	dev->c_dev.owner = THIS_MODULE;
	dev->c_dev.ops = &scr24x_fops;
	ret = cdev_add(&dev->c_dev, MKDEV(MAJOR(scr24x_devt), dev->devno), 1);
	if (ret < 0)
		goto err;

	ret = pcmcia_enable_device(link);
	if (ret < 0) {
		pcmcia_disable_device(link);
		goto err;
	}

	device_create(scr24x_class, NULL, MKDEV(MAJOR(scr24x_devt), dev->devno),
		      NULL, "scr24x%d", dev->devno);

	dev_info(&link->dev, "SCR24x Chip Card Interface\n");
	return 0;

err:
	if (dev->devno < SCR24X_DEVS)
		clear_bit(dev->devno, scr24x_minors);
	kfree (dev);
	return ret;
}