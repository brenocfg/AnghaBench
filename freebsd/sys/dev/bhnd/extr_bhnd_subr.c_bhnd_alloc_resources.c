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
typedef  size_t u_int ;
struct resource_spec {int type; int flags; int /*<<< orphan*/  rid; } ;
struct bhnd_resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_OPTIONAL ; 
 struct bhnd_resource* bhnd_alloc_resource_any (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bhnd_release_resources (int /*<<< orphan*/ ,struct resource_spec*,struct bhnd_resource**) ; 

int
bhnd_alloc_resources(device_t dev, struct resource_spec *rs,
    struct bhnd_resource **res)
{
	/* Initialize output array */
	for (u_int i = 0; rs[i].type != -1; i++)
		res[i] = NULL;

	for (u_int i = 0; rs[i].type != -1; i++) {
		res[i] = bhnd_alloc_resource_any(dev, rs[i].type, &rs[i].rid,
		    rs[i].flags);

		/* Clean up all allocations on failure */
		if (res[i] == NULL && !(rs[i].flags & RF_OPTIONAL)) {
			bhnd_release_resources(dev, rs, res);
			return (ENXIO);
		}
	}

	return (0);
}