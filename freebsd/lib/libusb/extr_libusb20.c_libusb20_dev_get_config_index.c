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
typedef  int uint8_t ;
struct libusb20_device {TYPE_1__* methods; int /*<<< orphan*/  is_opened; } ;
struct TYPE_2__ {int (* get_config_index ) (struct libusb20_device*,int*) ;} ;

/* Variables and functions */
 scalar_t__ libusb20_dev_close (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct libusb20_device*,int*) ; 

uint8_t
libusb20_dev_get_config_index(struct libusb20_device *pdev)
{
	int error;
	uint8_t cfg_index;
	uint8_t do_close;

	if (!pdev->is_opened) {
		error = libusb20_dev_open(pdev, 0);
		if (error == 0) {
			do_close = 1;
		} else {
			do_close = 0;
		}
	} else {
		do_close = 0;
	}

	error = pdev->methods->get_config_index(pdev, &cfg_index);
	if (error)
		cfg_index = 0xFF;	/* current config index */
	if (do_close) {
		if (libusb20_dev_close(pdev)) {
			/* ignore */
		}
	}
	return (cfg_index);
}