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
struct kobject {int dummy; } ;
struct brd_device {int /*<<< orphan*/  brd_disk; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brd_devices_mutex ; 
 struct brd_device* brd_init_one (int,int*) ; 
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 
 int max_part ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kobject *brd_probe(dev_t dev, int *part, void *data)
{
	struct brd_device *brd;
	struct kobject *kobj;
	bool new;

	mutex_lock(&brd_devices_mutex);
	brd = brd_init_one(MINOR(dev) / max_part, &new);
	kobj = brd ? get_disk_and_module(brd->brd_disk) : NULL;
	mutex_unlock(&brd_devices_mutex);

	if (new)
		*part = 0;

	return kobj;
}