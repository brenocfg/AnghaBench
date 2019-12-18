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
struct isa_pnp_id {scalar_t__ ip_id; scalar_t__ ip_desc; } ;
struct isa_device {scalar_t__ id_logicalid; scalar_t__ id_compatid; int /*<<< orphan*/  id_vendorid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
isa_pnp_probe(device_t dev, device_t child, struct isa_pnp_id *ids)
{
	struct isa_device* idev = DEVTOISA(child);

	if (!idev->id_vendorid)
		return (ENOENT);

	while (ids && ids->ip_id) {
		/*
		 * Really ought to support >1 compat id per device.
		 */
		if (idev->id_logicalid == ids->ip_id
		    || idev->id_compatid == ids->ip_id) {
			if (ids->ip_desc)
				device_set_desc(child, ids->ip_desc);
			return (0);
		}
		ids++;
	}

	return (ENXIO);
}