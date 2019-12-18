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
struct nbd_device {int /*<<< orphan*/  task_recv; } ;
struct gendisk {scalar_t__ private_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pid_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct gendisk *disk = dev_to_disk(dev);
	struct nbd_device *nbd = (struct nbd_device *)disk->private_data;

	return sprintf(buf, "%d\n", task_pid_nr(nbd->task_recv));
}