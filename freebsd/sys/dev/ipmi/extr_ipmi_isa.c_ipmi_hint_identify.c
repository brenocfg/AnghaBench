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
struct ipmi_get_info {int address; int io_mode; int offset; int /*<<< orphan*/  iface_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MODE ; 
 int /*<<< orphan*/  KCS_MODE ; 
 int /*<<< orphan*/  SMIC_MODE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct ipmi_get_info*,int) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 
 scalar_t__ resource_string_value (char const*,int,char*,char const**) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
ipmi_hint_identify(device_t dev, struct ipmi_get_info *info)
{
	const char *mode, *name;
	int i, unit, val;

	/* We require at least a "mode" hint. */
	name = device_get_name(dev);
	unit = device_get_unit(dev);
	if (resource_string_value(name, unit, "mode", &mode) != 0)
		return (0);

	/* Set the mode and default I/O resources for each mode. */
	bzero(info, sizeof(struct ipmi_get_info));
	if (strcasecmp(mode, "KCS") == 0) {
		info->iface_type = KCS_MODE;
		info->address = 0xca2;
		info->io_mode = 1;
		info->offset = 1;
	} else if (strcasecmp(mode, "SMIC") == 0) {
		info->iface_type = SMIC_MODE;
		info->address = 0xca9;
		info->io_mode = 1;
		info->offset = 1;
	} else if (strcasecmp(mode, "BT") == 0) {
		info->iface_type = BT_MODE;
		info->address = 0xe4;
		info->io_mode = 1;
		info->offset = 1;
	} else {
		device_printf(dev, "Invalid mode %s\n", mode);
		return (0);
	}

	/*
	 * Kill any resources that isahint.c might have setup for us
	 * since it will conflict with how we do resources.
	 */
	for (i = 0; i < 2; i++) {
		bus_delete_resource(dev, SYS_RES_MEMORY, i);
		bus_delete_resource(dev, SYS_RES_IOPORT, i);
	}

	/* Allow the I/O address to be overriden via hints. */
	if (resource_int_value(name, unit, "port", &val) == 0 && val != 0) {
		info->address = val;
		info->io_mode = 1;
	} else if (resource_int_value(name, unit, "maddr", &val) == 0 &&
	    val != 0) {
		info->address = val;
		info->io_mode = 0;
	}

	/* Allow the spacing to be overriden. */
	if (resource_int_value(name, unit, "spacing", &val) == 0) {
		switch (val) {
		case 8:
			info->offset = 1;
			break;
		case 16:
			info->offset = 2;
			break;
		case 32:
			info->offset = 4;
			break;
		default:
			device_printf(dev, "Invalid register spacing\n");
			return (0);
		}
	}
	return (1);
}