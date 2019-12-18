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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {int intr_en; scalar_t__ intr_flag; } ;
struct siba_devinfo {TYPE_1__ core_id; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BHND_BUS_GET_INTR_IVEC (scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 scalar_t__ siba_get_intr_count (scalar_t__,scalar_t__) ; 

int
siba_get_intr_ivec(device_t dev, device_t child, u_int intr, u_int *ivec)
{
	struct siba_devinfo	*dinfo;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev)
		return (BHND_BUS_GET_INTR_IVEC(device_get_parent(dev), child,
		    intr, ivec));

	/* Must be a valid interrupt ID */
	if (intr >= siba_get_intr_count(dev, child))
		return (ENXIO);

	KASSERT(intr == 0, ("invalid ivec %u", intr));

	dinfo = device_get_ivars(child);

	KASSERT(dinfo->core_id.intr_en,
	    ("core does not have an interrupt assigned"));

	*ivec = dinfo->core_id.intr_flag;
	return (0);
}