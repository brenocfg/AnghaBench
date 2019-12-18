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
typedef  scalar_t__ usb_timeout_t ;
typedef  void* uint8_t ;
struct bbb_transfer {size_t data_len; size_t data_rem; int error; size_t cmd_len; size_t state; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cv; int /*<<< orphan*/ * xfer; TYPE_1__* cbw; scalar_t__ actlen; scalar_t__ data_timeout; void* data_ptr; void* dir; void* lun; } ;
struct TYPE_2__ {scalar_t__ CBWCDB; } ;

/* Variables and functions */
 void* DIR_NONE ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,char*,char*) ; 
 scalar_t__ USB_MS_HZ ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbd_transfer_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bbb_command_start(struct bbb_transfer *sc, uint8_t dir, uint8_t lun,
    void *data_ptr, size_t data_len, void *cmd_ptr, size_t cmd_len,
    usb_timeout_t data_timeout)
{
	sc->lun = lun;
	sc->dir = data_len ? dir : DIR_NONE;
	sc->data_ptr = data_ptr;
	sc->data_len = data_len;
	sc->data_rem = data_len;
	sc->data_timeout = (data_timeout + USB_MS_HZ);
	sc->actlen = 0;
	sc->error = 0;
	sc->cmd_len = cmd_len;
	memset(&sc->cbw->CBWCDB, 0, sizeof(sc->cbw->CBWCDB));
	memcpy(&sc->cbw->CBWCDB, cmd_ptr, cmd_len);
	DPRINTFN(1, "SCSI cmd = %*D\n", (int)cmd_len, (char *)sc->cbw->CBWCDB, ":");

	USB_MTX_LOCK(&sc->mtx);
	usbd_transfer_start(sc->xfer[sc->state]);

	while (usbd_transfer_pending(sc->xfer[sc->state])) {
		cv_wait(&sc->cv, &sc->mtx);
	}
	USB_MTX_UNLOCK(&sc->mtx);
	return (sc->error);
}