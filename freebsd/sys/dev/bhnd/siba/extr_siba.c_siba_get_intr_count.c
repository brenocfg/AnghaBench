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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  intr_en; } ;
struct siba_devinfo {TYPE_1__ core_id; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BHND_BUS_GET_INTR_COUNT (scalar_t__,scalar_t__) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

u_int
siba_get_intr_count(device_t dev, device_t child)
{
	struct siba_devinfo	*dinfo;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev)
		return (BHND_BUS_GET_INTR_COUNT(device_get_parent(dev), child));

	dinfo = device_get_ivars(child);
	if (!dinfo->core_id.intr_en) {
		/* No interrupts */
		return (0);
	} else {
		/* One assigned interrupt */
		return (1);
	}
}