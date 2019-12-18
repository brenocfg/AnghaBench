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
typedef  int /*<<< orphan*/  device_t ;
typedef  int bhnd_device_order ;

/* Variables and functions */
#define  BHND_DEVICE_ORDER_ATTACH 129 
#define  BHND_DEVICE_ORDER_DETACH 128 
 int EINVAL ; 
 int compare_ascending_probe_order (void const*,void const*) ; 
 int compare_descending_probe_order (void const*,void const*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int (*) (void const*,void const*)) ; 

int
bhnd_sort_devices(device_t *devlist, size_t devcount, bhnd_device_order order)
{
	int (*compare)(const void *, const void *);

	switch (order) {
	case BHND_DEVICE_ORDER_ATTACH:
		compare = compare_ascending_probe_order;
		break;
	case BHND_DEVICE_ORDER_DETACH:
		compare = compare_descending_probe_order;
		break;
	default:
		printf("unknown sort order: %d\n", order);
		return (EINVAL);
	}

	qsort(devlist, devcount, sizeof(*devlist), compare);
	return (0);
}