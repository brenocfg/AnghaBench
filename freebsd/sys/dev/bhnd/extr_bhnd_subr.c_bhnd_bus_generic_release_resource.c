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
struct bhnd_resource {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bhnd_resource*,int /*<<< orphan*/ ) ; 

int
bhnd_bus_generic_release_resource(device_t dev, device_t child, int type,
    int rid, struct bhnd_resource *r)
{
	int error;

	if ((error = BUS_RELEASE_RESOURCE(dev, child, type, rid, r->res)))
		return (error);

	free(r, M_BHND);
	return (0);
}