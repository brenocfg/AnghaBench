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
struct lm75_snmp_sensor {int /*<<< orphan*/  parent; int /*<<< orphan*/  pnpinfo; int /*<<< orphan*/  location; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_sensor_sysctl (int /*<<< orphan*/ ,size_t*,int,char*) ; 

__attribute__((used)) static void
update_sensor(struct lm75_snmp_sensor *sensor, int idx)
{
	size_t len;

	len = sizeof(sensor->desc);
	update_sensor_sysctl(sensor->desc, &len, idx, "%desc");

	len = sizeof(sensor->location);
	update_sensor_sysctl(sensor->location, &len, idx, "%location");

	len = sizeof(sensor->pnpinfo);
	update_sensor_sysctl(sensor->pnpinfo, &len, idx, "%pnpinfo");

	len = sizeof(sensor->parent);
	update_sensor_sysctl(sensor->parent, &len, idx, "%parent");
}