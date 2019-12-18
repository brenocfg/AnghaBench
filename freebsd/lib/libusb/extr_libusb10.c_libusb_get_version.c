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
struct libusb_version {int dummy; } ;

/* Variables and functions */
 struct libusb_version const libusb_version ; 

const struct libusb_version *
libusb_get_version(void)
{

	return (&libusb_version);
}