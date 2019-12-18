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
struct opal_dev {int /*<<< orphan*/ * send_recv; void* data; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  unlk_lst; } ;
typedef  int /*<<< orphan*/  sec_send_recv ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ check_opal_support (struct opal_dev*) ; 
 int /*<<< orphan*/  kfree (struct opal_dev*) ; 
 struct opal_dev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct opal_dev *init_opal_dev(void *data, sec_send_recv *send_recv)
{
	struct opal_dev *dev;

	dev = kmalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	INIT_LIST_HEAD(&dev->unlk_lst);
	mutex_init(&dev->dev_lock);
	dev->data = data;
	dev->send_recv = send_recv;
	if (check_opal_support(dev) != 0) {
		pr_debug("Opal is not supported on this device\n");
		kfree(dev);
		return NULL;
	}

	return dev;
}