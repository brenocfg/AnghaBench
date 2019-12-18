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
typedef  int /*<<< orphan*/  u_int ;
struct bcma_devinfo {int /*<<< orphan*/  num_intrs; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BUS_GET_INTR_COUNT (scalar_t__,scalar_t__) ; 
 struct bcma_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

u_int
bcma_get_intr_count(device_t dev, device_t child)
{
	struct bcma_devinfo *dinfo;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev)
		return (BHND_BUS_GET_INTR_COUNT(device_get_parent(dev), child));

	dinfo = device_get_ivars(child);
	return (dinfo->num_intrs);
}