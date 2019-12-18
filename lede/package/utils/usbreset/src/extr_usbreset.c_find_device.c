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
struct usbentry {int bus_num; int dev_num; int vendor_id; int product_id; int /*<<< orphan*/  product_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct usbentry* parse_devlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

struct usbentry * find_device(int *bus, int *dev,
                              int *vid, int *pid,
                              const char *product)
{
	DIR *devs = opendir("/sys/bus/usb/devices");

	struct usbentry *e, *match = NULL;

	if (!devs)
		return NULL;

	while ((e = parse_devlist(devs)) != NULL)
	{
		if ((bus && (e->bus_num == *bus) && (e->dev_num == *dev)) ||
			(vid && (e->vendor_id == *vid) && (e->product_id == *pid)) ||
			(product && !strcasecmp(e->product_name, product)))
		{
			match = e;
			break;
		}
	}

	closedir(devs);

	return match;
}