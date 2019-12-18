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
struct libusb20_device {int dummy; } ;
struct TYPE_2__ {int bConfigurationValue; } ;
struct libusb20_config {TYPE_1__ desc; } ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_MEM ; 
 int /*<<< orphan*/  free (struct libusb20_config*) ; 
 struct libusb20_config* libusb20_dev_alloc_config (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_dev_get_config_index (struct libusb20_device*) ; 

int
libusb_get_configuration(struct libusb20_device *pdev, int *config)
{
	struct libusb20_config *pconf;

	if (pdev == NULL || config == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	pconf = libusb20_dev_alloc_config(pdev, libusb20_dev_get_config_index(pdev));
	if (pconf == NULL)
		return (LIBUSB_ERROR_NO_MEM);

	*config = pconf->desc.bConfigurationValue;

	free(pconf);

	return (0);
}