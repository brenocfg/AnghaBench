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
typedef  scalar_t__ device_t ;
typedef  TYPE_1__* devclass_t ;
struct TYPE_4__ {int maxunit; scalar_t__* devices; } ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int devclass_get_count (TYPE_1__*) ; 
 scalar_t__* malloc (int,int /*<<< orphan*/ ,int) ; 

int
devclass_get_devices(devclass_t dc, device_t **devlistp, int *devcountp)
{
	int count, i;
	device_t *list;

	count = devclass_get_count(dc);
	list = malloc(count * sizeof(device_t), M_TEMP, M_NOWAIT|M_ZERO);
	if (!list)
		return (ENOMEM);

	count = 0;
	for (i = 0; i < dc->maxunit; i++) {
		if (dc->devices[i]) {
			list[count] = dc->devices[i];
			count++;
		}
	}

	*devlistp = list;
	*devcountp = count;

	return (0);
}