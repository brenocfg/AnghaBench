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
struct mii_attach_args {scalar_t__ mii_id1; scalar_t__ mii_id2; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 scalar_t__ DC_DEVICEID_21143 ; 
 scalar_t__ DC_VENDORID_DEC ; 
 int ENXIO ; 
 struct mii_attach_args* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
dcphy_probe(device_t dev)
{
	struct mii_attach_args *ma;

	ma = device_get_ivars(dev);

	/*
	 * The dc driver will report the 21143 vendor and device
	 * ID to let us know that it wants us to attach.
	 */
	if (ma->mii_id1 != DC_VENDORID_DEC ||
	    ma->mii_id2 != DC_DEVICEID_21143)
		return (ENXIO);

	device_set_desc(dev, "Intel 21143 NWAY media interface");

	return (BUS_PROBE_DEFAULT);
}