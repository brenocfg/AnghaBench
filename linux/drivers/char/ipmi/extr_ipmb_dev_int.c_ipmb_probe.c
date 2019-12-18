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
struct TYPE_5__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct ipmb_dev {TYPE_2__ miscdev; struct i2c_client* client; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  request_queue_len; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 struct ipmb_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ipmb_dev*) ; 
 int i2c_slave_register (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmb_fops ; 
 int /*<<< orphan*/  ipmb_slave_cb ; 
 int /*<<< orphan*/  misc_deregister (TYPE_2__*) ; 
 int misc_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmb_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ipmb_dev *ipmb_dev;
	int ret;

	ipmb_dev = devm_kzalloc(&client->dev, sizeof(*ipmb_dev),
					GFP_KERNEL);
	if (!ipmb_dev)
		return -ENOMEM;

	spin_lock_init(&ipmb_dev->lock);
	init_waitqueue_head(&ipmb_dev->wait_queue);
	atomic_set(&ipmb_dev->request_queue_len, 0);
	INIT_LIST_HEAD(&ipmb_dev->request_queue);

	mutex_init(&ipmb_dev->file_mutex);

	ipmb_dev->miscdev.minor = MISC_DYNAMIC_MINOR;

	ipmb_dev->miscdev.name = devm_kasprintf(&client->dev, GFP_KERNEL,
						"%s%d", "ipmb-",
						client->adapter->nr);
	ipmb_dev->miscdev.fops = &ipmb_fops;
	ipmb_dev->miscdev.parent = &client->dev;
	ret = misc_register(&ipmb_dev->miscdev);
	if (ret)
		return ret;

	ipmb_dev->client = client;
	i2c_set_clientdata(client, ipmb_dev);
	ret = i2c_slave_register(client, ipmb_slave_cb);
	if (ret) {
		misc_deregister(&ipmb_dev->miscdev);
		return ret;
	}

	return 0;
}