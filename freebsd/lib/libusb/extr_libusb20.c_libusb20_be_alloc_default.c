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
 struct libusb20_backend* libusb20_be_alloc_linux () ; 
 struct libusb20_backend* libusb20_be_alloc_ugen20 () ; 

struct libusb20_backend *
libusb20_be_alloc_default(void)
{
	struct libusb20_backend *pbe;

#ifdef __linux__
	pbe = libusb20_be_alloc_linux();
	if (pbe) {
		return (pbe);
	}
#endif
	pbe = libusb20_be_alloc_ugen20();
	if (pbe) {
		return (pbe);
	}
	return (NULL);			/* no backend found */
}