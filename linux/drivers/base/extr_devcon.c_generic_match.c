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
struct device_connection {int /*<<< orphan*/ * endpoint; scalar_t__ fwnode; } ;
typedef  void device ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* bus_find_device_by_name (struct bus_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* device_connection_fwnode_match (struct device_connection*) ; 
 struct bus_type** generic_match_buses ; 

__attribute__((used)) static void *generic_match(struct device_connection *con, int ep, void *data)
{
	struct bus_type *bus;
	struct device *dev;

	if (con->fwnode)
		return device_connection_fwnode_match(con);

	for (bus = generic_match_buses[0]; bus; bus++) {
		dev = bus_find_device_by_name(bus, NULL, con->endpoint[ep]);
		if (dev)
			return dev;
	}

	/*
	 * We only get called if a connection was found, tell the caller to
	 * wait for the other device to show up.
	 */
	return ERR_PTR(-EPROBE_DEFER);
}