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
struct libusb20_backend {int dummy; } ;

/* Variables and functions */
 struct libusb20_backend* libusb20_be_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_ugen20_backend ; 

struct libusb20_backend *
libusb20_be_alloc_ugen20(void)
{
	return (libusb20_be_alloc(&libusb20_ugen20_backend));
}