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
struct libusb20_device {TYPE_1__* beMethods; } ;
struct TYPE_2__ {char const* (* get_backend_name ) () ;} ;

/* Variables and functions */
 char const* stub1 () ; 

const char *
libusb20_dev_get_backend_name(struct libusb20_device *pdev)
{
	return (pdev->beMethods->get_backend_name());
}