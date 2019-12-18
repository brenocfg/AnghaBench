#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct port_info {long port_id; } ;
struct adapter {TYPE_1__* names; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* ifnet_name; } ;

/* Variables and functions */
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_find_dev (int*,char const*,int*,char*,char const*) ; 
 scalar_t__ resource_long_value (char const*,int,char*,long*) ; 

__attribute__((used)) static int
t4_ifnet_unit(struct adapter *sc, struct port_info *pi)
{
	const char *parent, *name;
	long value;
	int line, unit;

	line = 0;
	parent = device_get_nameunit(sc->dev);
	name = sc->names->ifnet_name;
	while (resource_find_dev(&line, name, &unit, "at", parent) == 0) {
		if (resource_long_value(name, unit, "port", &value) == 0 &&
		    value == pi->port_id)
			return (unit);
	}
	return (-1);
}