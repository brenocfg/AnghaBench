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
typedef  int u_int ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCF_NAME ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
pcf_isa_probe(device_t dev)
{
	rman_res_t	start, count;
	u_int		rid = 0, port, error;

	/* skip PnP probes */
	if (isa_get_logicalid(dev))
		return (ENXIO);

	/* The port address must be explicitly specified */
	bus_get_resource(dev, SYS_RES_IOPORT, rid, &start, &count);
	if ((error = resource_int_value(PCF_NAME, 0, "port", &port)) != 0)
		return (error);

	/* Probe is only successful for the specified base io */
	if (port != (u_int)start)
		return (ENXIO);

	device_set_desc(dev, "PCF8584 I2C bus controller");

	return (0);
}