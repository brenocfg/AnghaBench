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
struct bhnd_chipid {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct bhnd_chipid const* BHND_BUS_GET_CHIPID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

const struct bhnd_chipid *
bhnd_bus_generic_get_chipid(device_t dev, device_t child)
{
	if (device_get_parent(dev) != NULL)
		return (BHND_BUS_GET_CHIPID(device_get_parent(dev), child));

	panic("missing BHND_BUS_GET_CHIPID()");
}