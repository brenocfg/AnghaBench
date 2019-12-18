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
struct uio {size_t uio_resid; TYPE_1__* uio_td; } ;
struct tpm_sc {scalar_t__ pending_data_length; int (* transmit ) (struct tpm_sc*,size_t) ;int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  owner_tid; int /*<<< orphan*/  discard_buffer_callout; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_cv; int /*<<< orphan*/  dev; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 size_t TPM_BUFSIZE ; 
 size_t TPM_HEADER_SIZE ; 
 int TPM_READ_TIMEOUT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct tpm_sc*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct tpm_sc*,size_t) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int tick ; 
 int /*<<< orphan*/  tpm20_discard_buffer ; 
 int uiomove (int /*<<< orphan*/ ,size_t,struct uio*) ; 

int
tpm20_write(struct cdev *dev, struct uio *uio, int flags)
{
	struct tpm_sc *sc;
	size_t byte_count;
	int result = 0;

	sc = (struct tpm_sc *)dev->si_drv1;

	byte_count = uio->uio_resid;
	if (byte_count < TPM_HEADER_SIZE) {
		device_printf(sc->dev,
		    "Requested transfer is too small\n");
		return (EINVAL);
	}

	if (byte_count > TPM_BUFSIZE) {
		device_printf(sc->dev,
		    "Requested transfer is too large\n");
		return (E2BIG);
	}

	sx_xlock(&sc->dev_lock);

	while (sc->pending_data_length != 0)
		cv_wait(&sc->buf_cv, &sc->dev_lock);

	result = uiomove(sc->buf, byte_count, uio);
	if (result != 0) {
		sx_xunlock(&sc->dev_lock);
		return (result);
	}

	result = sc->transmit(sc, byte_count);

	if (result == 0) {
		callout_reset(&sc->discard_buffer_callout,
		    TPM_READ_TIMEOUT / tick, tpm20_discard_buffer, sc);
		sc->owner_tid = uio->uio_td->td_tid;
	}

	sx_xunlock(&sc->dev_lock);
	return (result);
}