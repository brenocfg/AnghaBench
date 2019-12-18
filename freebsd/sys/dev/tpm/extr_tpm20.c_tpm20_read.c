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
struct uio {int /*<<< orphan*/  uio_resid; TYPE_1__* uio_td; } ;
struct tpm_sc {scalar_t__ owner_tid; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  buf_cv; scalar_t__ pending_data_length; scalar_t__ buf; int /*<<< orphan*/  discard_buffer_callout; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {scalar_t__ td_tid; } ;

/* Variables and functions */
 int EPERM ; 
 int ETIMEDOUT ; 
 size_t MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_BUFSIZE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int uiomove (int /*<<< orphan*/ ,size_t,struct uio*) ; 

int
tpm20_read(struct cdev *dev, struct uio *uio, int flags)
{
	struct tpm_sc *sc;
	size_t bytes_to_transfer;
	int result = 0;

	sc = (struct tpm_sc *)dev->si_drv1;

	callout_stop(&sc->discard_buffer_callout);
	sx_xlock(&sc->dev_lock);
	if (sc->owner_tid != uio->uio_td->td_tid) {
		sx_xunlock(&sc->dev_lock);
		return (EPERM);
	}

	bytes_to_transfer = MIN(sc->pending_data_length, uio->uio_resid);
	if (bytes_to_transfer > 0) {
		result = uiomove((caddr_t) sc->buf, bytes_to_transfer, uio);
		memset(sc->buf, 0, TPM_BUFSIZE);
		sc->pending_data_length = 0;
		cv_signal(&sc->buf_cv);
	} else {
		result = ETIMEDOUT;
	}

	sx_xunlock(&sc->dev_lock);

	return (result);
}