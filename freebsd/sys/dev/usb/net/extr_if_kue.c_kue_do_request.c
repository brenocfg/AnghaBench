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
typedef  int usb_error_t ;
struct usb_device_request {int dummy; } ;
struct kue_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,void*,int) ; 

__attribute__((used)) static int
kue_do_request(struct kue_softc *sc, struct usb_device_request *req,
    void *data)
{
	usb_error_t err;

	err = uether_do_request(&sc->sc_ue, req, data, 60000);

	return (err);
}