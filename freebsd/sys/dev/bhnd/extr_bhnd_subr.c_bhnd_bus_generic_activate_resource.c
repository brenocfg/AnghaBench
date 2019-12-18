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
struct bhnd_resource {int direct; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int BHND_BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,struct bhnd_resource*) ; 
 int ENODEV ; 
 int bus_activate_resource (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
bhnd_bus_generic_activate_resource(device_t dev, device_t child, int type,
    int rid, struct bhnd_resource *r)
{
	int	error;
	bool	passthrough;

	passthrough = (device_get_parent(child) != dev);

	/* Try to delegate to the parent */
	if (device_get_parent(dev) != NULL) {
		error = BHND_BUS_ACTIVATE_RESOURCE(device_get_parent(dev),
		    child, type, rid, r);
	} else {
		error = ENODEV;
	}

	/* If bhnd(4) activation has failed and we're the child's direct
	 * parent, try falling back on standard resource activation.
	 */
	if (error && !passthrough) {
		error = bus_activate_resource(child, type, rid, r->res);
		if (!error)
			r->direct = true;
	}

	return (error);
}