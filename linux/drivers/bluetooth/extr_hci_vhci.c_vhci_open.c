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
struct vhci_data {int /*<<< orphan*/  open_timeout; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  readq; } ;
struct inode {int dummy; } ;
struct file {struct vhci_data* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct vhci_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhci_open_timeout ; 

__attribute__((used)) static int vhci_open(struct inode *inode, struct file *file)
{
	struct vhci_data *data;

	data = kzalloc(sizeof(struct vhci_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	skb_queue_head_init(&data->readq);
	init_waitqueue_head(&data->read_wait);

	mutex_init(&data->open_mutex);
	INIT_DELAYED_WORK(&data->open_timeout, vhci_open_timeout);

	file->private_data = data;
	nonseekable_open(inode, file);

	schedule_delayed_work(&data->open_timeout, msecs_to_jiffies(1000));

	return 0;
}