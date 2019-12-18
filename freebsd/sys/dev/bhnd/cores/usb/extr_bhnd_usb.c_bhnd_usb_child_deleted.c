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
struct bhnd_usb_devinfo {int /*<<< orphan*/  sdi_rl; int /*<<< orphan*/  sdi_irq; scalar_t__ sdi_irq_mapped; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bhnd_unmap_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_usb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bhnd_usb_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bhnd_usb_child_deleted(device_t dev, device_t child)
{
	struct bhnd_usb_devinfo	*dinfo;

	if ((dinfo = device_get_ivars(child)) == NULL)
		return;

	if (dinfo->sdi_irq_mapped)
		bhnd_unmap_intr(dev, dinfo->sdi_irq);

	resource_list_free(&dinfo->sdi_rl);
	free(dinfo, M_DEVBUF);
}