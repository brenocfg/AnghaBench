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
typedef  int /*<<< orphan*/  romid_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 int ow_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow_check_crc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ow_child_by_romid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_device_found(device_t dev, romid_t romid)
{

	/* XXX Move this up into enumerate? */
	/*
	 * All valid ROM IDs have a valid CRC. Check that first.
	 */
	if (!ow_check_crc(romid)) {
		device_printf(dev, "Device romid %8D failed CRC.\n",
		    &romid, ":");
		return EINVAL;
	}

	/*
	 * If we've seen this child before, don't add a new one for it.
	 */
	if (ow_child_by_romid(dev, romid) != NULL)
		return 0;

	return ow_add_child(dev, romid);
}