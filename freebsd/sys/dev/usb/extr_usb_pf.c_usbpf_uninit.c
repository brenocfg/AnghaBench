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
struct usb_bus {int /*<<< orphan*/ * ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/ * devclass_find (int /*<<< orphan*/ ) ; 
 int devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 struct usb_bus* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbpf_clone_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbpf_cloner ; 
 int /*<<< orphan*/  usbusname ; 

__attribute__((used)) static void
usbpf_uninit(void *arg)
{
	int devlcnt;
	device_t *devlp;
	devclass_t dc;
	struct usb_bus *ubus;
	int error;
	int i;
	
	if_clone_detach(usbpf_cloner);

	dc = devclass_find(usbusname);
	if (dc == NULL)
		return;
	error = devclass_get_devices(dc, &devlp, &devlcnt);
	if (error)
		return;
	for (i = 0; i < devlcnt; i++) {
		ubus = device_get_softc(devlp[i]);
		if (ubus != NULL && ubus->ifp != NULL)
			usbpf_clone_destroy(usbpf_cloner, ubus->ifp);
	}
	free(devlp, M_TEMP);
}