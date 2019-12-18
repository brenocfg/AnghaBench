#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int bNumConfigurations; } ;
struct libusb20_device {TYPE_1__* methods; int /*<<< orphan*/  is_opened; TYPE_2__ ddesc; } ;
struct libusb20_config {int dummy; } ;
struct TYPE_3__ {int (* get_config_desc_full ) (struct libusb20_device*,int**,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int libusb20_dev_close (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 struct libusb20_config* libusb20_parse_config_desc (int*) ; 
 int stub1 (struct libusb20_device*,int**,int /*<<< orphan*/ *,int) ; 

struct libusb20_config *
libusb20_dev_alloc_config(struct libusb20_device *pdev, uint8_t configIndex)
{
	struct libusb20_config *retval = NULL;
	uint8_t *ptr;
	uint16_t len;
	uint8_t do_close;
	int error;

	/*
	 * Catch invalid configuration descriptor reads early on to
	 * avoid issues with devices that don't check for a valid USB
	 * configuration read request.
	 */
	if (configIndex >= pdev->ddesc.bNumConfigurations)
		return (NULL);

	if (!pdev->is_opened) {
		error = libusb20_dev_open(pdev, 0);
		if (error) {
			return (NULL);
		}
		do_close = 1;
	} else {
		do_close = 0;
	}
	error = pdev->methods->get_config_desc_full(pdev,
	    &ptr, &len, configIndex);

	if (error) {
		goto done;
	}
	/* parse new config descriptor */
	retval = libusb20_parse_config_desc(ptr);

	/* free config descriptor */
	free(ptr);

done:
	if (do_close) {
		error = libusb20_dev_close(pdev);
	}
	return (retval);
}