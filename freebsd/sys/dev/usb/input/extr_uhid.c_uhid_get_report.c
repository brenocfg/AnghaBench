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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct uhid_softc {int /*<<< orphan*/  sc_iface_index; int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyout (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_req_get_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
uhid_get_report(struct uhid_softc *sc, uint8_t type,
    uint8_t id, void *kern_data, void *user_data,
    uint16_t len)
{
	int err;
	uint8_t free_data = 0;

	if (kern_data == NULL) {
		kern_data = malloc(len, M_USBDEV, M_WAITOK);
		if (kern_data == NULL) {
			err = ENOMEM;
			goto done;
		}
		free_data = 1;
	}
	err = usbd_req_get_report(sc->sc_udev, NULL, kern_data,
	    len, sc->sc_iface_index, type, id);
	if (err) {
		err = ENXIO;
		goto done;
	}
	if (user_data) {
		/* dummy buffer */
		err = copyout(kern_data, user_data, len);
		if (err) {
			goto done;
		}
	}
done:
	if (free_data) {
		free(kern_data, M_USBDEV);
	}
	return (err);
}