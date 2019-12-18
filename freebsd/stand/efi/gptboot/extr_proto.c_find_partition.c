#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devpath; struct TYPE_4__* next; } ;
typedef  TYPE_1__ dev_info_t ;

/* Variables and functions */
 TYPE_1__* devices ; 
 int partition_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dev_info_t *
find_partition(int part)
{
	dev_info_t *dev;

	if (part == 0)
		return (NULL);
	for (dev = devices; dev != NULL; dev = dev->next)
		if (partition_number(dev->devpath) == part)
			break;
	return (dev);
}