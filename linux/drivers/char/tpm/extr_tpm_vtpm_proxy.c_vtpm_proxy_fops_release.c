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
struct proxy_dev {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct proxy_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtpm_proxy_delete_device (struct proxy_dev*) ; 

__attribute__((used)) static int vtpm_proxy_fops_release(struct inode *inode, struct file *filp)
{
	struct proxy_dev *proxy_dev = filp->private_data;

	filp->private_data = NULL;

	vtpm_proxy_delete_device(proxy_dev);

	return 0;
}