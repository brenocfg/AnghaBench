#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swim_priv {int floppy_count; TYPE_1__* unit; } ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kobject *floppy_find(dev_t dev, int *part, void *data)
{
	struct swim_priv *swd = data;
	int drive = (*part & 3);

	if (drive >= swd->floppy_count)
		return NULL;

	*part = 0;
	return get_disk_and_module(swd->unit[drive].disk);
}