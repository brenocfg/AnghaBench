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
typedef  int /*<<< orphan*/  libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  libusb_unref_device (int /*<<< orphan*/ *) ; 

void
libusb_free_device_list(libusb_device **list, int unref_devices)
{
	int i;

	if (list == NULL)
		return;			/* be NULL safe */

	if (unref_devices) {
		for (i = 0; list[i] != NULL; i++)
			libusb_unref_device(list[i]);
	}
	free(list);
}