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
struct scr24x_dev {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; int /*<<< orphan*/  devno; int /*<<< orphan*/  c_dev; } ;
struct pcmcia_device {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  scr24x_class ; 
 int /*<<< orphan*/  scr24x_delete ; 
 int /*<<< orphan*/  scr24x_devt ; 
 int /*<<< orphan*/  scr24x_minors ; 

__attribute__((used)) static void scr24x_remove(struct pcmcia_device *link)
{
	struct scr24x_dev *dev = (struct scr24x_dev *)link->priv;

	device_destroy(scr24x_class, MKDEV(MAJOR(scr24x_devt), dev->devno));
	mutex_lock(&dev->lock);
	pcmcia_disable_device(link);
	cdev_del(&dev->c_dev);
	clear_bit(dev->devno, scr24x_minors);
	dev->dev = NULL;
	mutex_unlock(&dev->lock);

	kref_put(&dev->refcnt, scr24x_delete);
}