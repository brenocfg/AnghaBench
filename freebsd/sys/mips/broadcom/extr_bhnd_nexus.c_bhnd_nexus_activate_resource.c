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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nexus_activate_resource(device_t dev, device_t child, int type, int rid,
    struct bhnd_resource *r)
{
	int error;

	/* Always direct */
	if ((error = bus_activate_resource(child, type, rid, r->res)))
		return (error);

	r->direct = true;
	return (0);
}