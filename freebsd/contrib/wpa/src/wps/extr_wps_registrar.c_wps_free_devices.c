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
struct wps_registrar_device {int /*<<< orphan*/  dev; struct wps_registrar_device* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wps_registrar_device*) ; 
 int /*<<< orphan*/  wps_device_data_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wps_free_devices(struct wps_registrar_device *dev)
{
	struct wps_registrar_device *prev;

	while (dev) {
		prev = dev;
		dev = dev->next;
		wps_device_data_free(&prev->dev);
		os_free(prev);
	}
}