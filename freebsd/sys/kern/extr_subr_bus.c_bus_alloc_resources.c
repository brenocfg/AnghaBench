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
struct resource_spec {int type; int flags; int /*<<< orphan*/  rid; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_OPTIONAL ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,struct resource_spec*,struct resource**) ; 

int
bus_alloc_resources(device_t dev, struct resource_spec *rs,
    struct resource **res)
{
	int i;

	for (i = 0; rs[i].type != -1; i++)
		res[i] = NULL;
	for (i = 0; rs[i].type != -1; i++) {
		res[i] = bus_alloc_resource_any(dev,
		    rs[i].type, &rs[i].rid, rs[i].flags);
		if (res[i] == NULL && !(rs[i].flags & RF_OPTIONAL)) {
			bus_release_resources(dev, rs, res);
			return (ENXIO);
		}
	}
	return (0);
}