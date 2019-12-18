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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
struct siba_devinfo {TYPE_1__** cfg_res; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ device_t ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  bhnd_bus_read_1 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  bhnd_bus_read_2 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  bhnd_bus_read_4 (TYPE_1__*,scalar_t__) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_read_config(device_t dev, device_t child, bus_size_t offset, void *value,
    u_int width)
{
	struct siba_devinfo	*dinfo;
	rman_res_t		 r_size;

	/* Must be directly attached */
	if (device_get_parent(child) != dev)
		return (EINVAL);

	/* CFG0 registers must be available */
	dinfo = device_get_ivars(child);
	if (dinfo->cfg_res[0] == NULL)
		return (ENODEV);

	/* Offset must fall within CFG0 */
	r_size = rman_get_size(dinfo->cfg_res[0]->res);
	if (r_size < offset || r_size - offset < width)
		return (EFAULT);

	switch (width) {
	case 1:
		*((uint8_t *)value) = bhnd_bus_read_1(dinfo->cfg_res[0],
		    offset);
		return (0);
	case 2:
		*((uint16_t *)value) = bhnd_bus_read_2(dinfo->cfg_res[0],
		    offset);
		return (0);
	case 4:
		*((uint32_t *)value) = bhnd_bus_read_4(dinfo->cfg_res[0],
		    offset);
		return (0);
	default:
		return (EINVAL);
	}
}