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
struct reader_dev {int /*<<< orphan*/  poll_timer; } ;
struct pcmcia_device {int open; struct reader_dev* priv; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct reader_dev* private_data; } ;

/* Variables and functions */
 int CM_MAX_DEV ; 
 int /*<<< orphan*/  DEBUGP (int,struct reader_dev*,char*) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int O_NONBLOCK ; 
 scalar_t__ POLL_PERIOD ; 
 int /*<<< orphan*/  cm4040_mutex ; 
 struct pcmcia_device** dev_table ; 
 int iminor (struct inode*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 

__attribute__((used)) static int cm4040_open(struct inode *inode, struct file *filp)
{
	struct reader_dev *dev;
	struct pcmcia_device *link;
	int minor = iminor(inode);
	int ret;

	if (minor >= CM_MAX_DEV)
		return -ENODEV;

	mutex_lock(&cm4040_mutex);
	link = dev_table[minor];
	if (link == NULL || !pcmcia_dev_present(link)) {
		ret = -ENODEV;
		goto out;
	}

	if (link->open) {
		ret = -EBUSY;
		goto out;
	}

	dev = link->priv;
	filp->private_data = dev;

	if (filp->f_flags & O_NONBLOCK) {
		DEBUGP(4, dev, "filep->f_flags O_NONBLOCK set\n");
		ret = -EAGAIN;
		goto out;
	}

	link->open = 1;

	mod_timer(&dev->poll_timer, jiffies + POLL_PERIOD);

	DEBUGP(2, dev, "<- cm4040_open (successfully)\n");
	ret = nonseekable_open(inode, filp);
out:
	mutex_unlock(&cm4040_mutex);
	return ret;
}