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
struct ipmi_file_private {int default_retries; scalar_t__ default_retry_time_ms; int /*<<< orphan*/  recv_mutex; int /*<<< orphan*/ * fasync_queue; int /*<<< orphan*/  wait; int /*<<< orphan*/  recv_msgs; int /*<<< orphan*/  recv_msg_lock; int /*<<< orphan*/  user; } ;
struct inode {int dummy; } ;
struct file {struct ipmi_file_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,struct ipmi_file_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_hndlrs ; 
 int /*<<< orphan*/  kfree (struct ipmi_file_private*) ; 
 struct ipmi_file_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmi_open(struct inode *inode, struct file *file)
{
	int                      if_num = iminor(inode);
	int                      rv;
	struct ipmi_file_private *priv;

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	rv = ipmi_create_user(if_num,
			      &ipmi_hndlrs,
			      priv,
			      &priv->user);
	if (rv) {
		kfree(priv);
		goto out;
	}

	file->private_data = priv;

	spin_lock_init(&priv->recv_msg_lock);
	INIT_LIST_HEAD(&priv->recv_msgs);
	init_waitqueue_head(&priv->wait);
	priv->fasync_queue = NULL;
	mutex_init(&priv->recv_mutex);

	/* Use the low-level defaults. */
	priv->default_retries = -1;
	priv->default_retry_time_ms = 0;

out:
	return rv;
}