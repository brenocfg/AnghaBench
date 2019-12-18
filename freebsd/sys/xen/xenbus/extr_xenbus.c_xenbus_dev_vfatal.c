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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateClosing ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xenbus_dev_verror (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xenbus_dev_vfatal(device_t dev, int err, const char *fmt, va_list ap)
{
	xenbus_dev_verror(dev, err, fmt, ap);
	device_printf(dev, "Fatal error. Transitioning to Closing State\n");
	xenbus_set_state(dev, XenbusStateClosing);
}