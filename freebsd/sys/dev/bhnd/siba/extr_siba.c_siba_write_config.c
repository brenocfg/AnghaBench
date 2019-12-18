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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_int ;
struct siba_devinfo {struct bhnd_resource** cfg_res; } ;
struct bhnd_resource {int /*<<< orphan*/  res; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  bhnd_bus_write_1 (struct bhnd_resource*,scalar_t__,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  bhnd_bus_write_2 (struct bhnd_resource*,scalar_t__,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (struct bhnd_resource*,scalar_t__,int /*<<< orphan*/  const) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_write_config(device_t dev, device_t child, bus_size_t offset,
    const void *value, u_int width)
{
	struct siba_devinfo	*dinfo;
	struct bhnd_resource	*r;
	rman_res_t		 r_size;

	/* Must be directly attached */
	if (device_get_parent(child) != dev)
		return (EINVAL);

	/* CFG0 registers must be available */
	dinfo = device_get_ivars(child);
	if ((r = dinfo->cfg_res[0]) == NULL)
		return (ENODEV);

	/* Offset must fall within CFG0 */
	r_size = rman_get_size(r->res);
	if (r_size < offset || r_size - offset < width)
		return (EFAULT);

	switch (width) {
	case 1:
		bhnd_bus_write_1(r, offset, *(const uint8_t *)value);
		return (0);
	case 2:
		bhnd_bus_write_2(r, offset, *(const uint8_t *)value);
		return (0);
	case 4:
		bhnd_bus_write_4(r, offset, *(const uint8_t *)value);
		return (0);
	default:
		return (EINVAL);
	}
}