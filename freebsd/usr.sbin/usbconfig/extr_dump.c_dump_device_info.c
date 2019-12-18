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
typedef  int uint8_t ;
struct libusb20_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* dump_mode (int /*<<< orphan*/ ) ; 
 char* dump_power_mode (int /*<<< orphan*/ ) ; 
 char* dump_speed (int /*<<< orphan*/ ) ; 
 int libusb20_dev_get_address (struct libusb20_device*) ; 
 int libusb20_dev_get_bus_number (struct libusb20_device*) ; 
 int libusb20_dev_get_config_index (struct libusb20_device*) ; 
 char* libusb20_dev_get_desc (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_get_iface_desc (struct libusb20_device*,int,char*,int) ; 
 int /*<<< orphan*/  libusb20_dev_get_mode (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_get_power_mode (struct libusb20_device*) ; 
 unsigned int libusb20_dev_get_power_usage (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_get_speed (struct libusb20_device*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_device_info(struct libusb20_device *pdev, uint8_t show_ifdrv)
{
	char buf[128];
	uint8_t n;
	unsigned int usage;

	usage = libusb20_dev_get_power_usage(pdev);

	printf("%s, cfg=%u md=%s spd=%s pwr=%s (%umA)\n",
	    libusb20_dev_get_desc(pdev),
	    libusb20_dev_get_config_index(pdev),
	    dump_mode(libusb20_dev_get_mode(pdev)),
	    dump_speed(libusb20_dev_get_speed(pdev)),
	    dump_power_mode(libusb20_dev_get_power_mode(pdev)),
	    usage);

	if (!show_ifdrv)
		return;

	for (n = 0; n != 255; n++) {
		if (libusb20_dev_get_iface_desc(pdev, n, buf, sizeof(buf)))
			break;
		if (buf[0] == 0)
			continue;
		printf("ugen%u.%u.%u: %s\n",
		    libusb20_dev_get_bus_number(pdev),
		    libusb20_dev_get_address(pdev), n, buf);
	}
}