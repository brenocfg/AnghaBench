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
struct device_connection {int /*<<< orphan*/  id; int /*<<< orphan*/  fwnode; } ;
typedef  void device ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 void* bus_find_device_by_fwnode (struct bus_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (void*) ; 
 struct bus_type** generic_match_buses ; 
 int /*<<< orphan*/  put_device (void*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *device_connection_fwnode_match(struct device_connection *con)
{
	struct bus_type *bus;
	struct device *dev;

	for (bus = generic_match_buses[0]; bus; bus++) {
		dev = bus_find_device_by_fwnode(bus, con->fwnode);
		if (dev && !strncmp(dev_name(dev), con->id, strlen(con->id)))
			return dev;

		put_device(dev);
	}
	return NULL;
}