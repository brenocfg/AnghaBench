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
struct uio {int uio_iovcnt; size_t uio_resid; int /*<<< orphan*/  uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct ha_softc {int ha_disconnect; int ha_wakeup; int /*<<< orphan*/  ha_lock; scalar_t__ ha_connected; int /*<<< orphan*/  ha_so; } ;
typedef  int /*<<< orphan*/  ctl_ha_status ;
typedef  int /*<<< orphan*/  ctl_ha_channel ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_STATUS_DISCONNECT ; 
 int /*<<< orphan*/  CTL_HA_STATUS_ERROR ; 
 int /*<<< orphan*/  CTL_HA_STATUS_SUCCESS ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  curthread ; 
 struct ha_softc ha_softc ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int soreceive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

ctl_ha_status
ctl_ha_msg_recv(ctl_ha_channel channel, void *addr, size_t len,
		int wait)
{
	struct ha_softc *softc = &ha_softc;
	struct uio uio;
	struct iovec iov;
	int error, flags;

	if (!softc->ha_connected)
		return (CTL_HA_STATUS_DISCONNECT);

	iov.iov_base = addr;
	iov.iov_len = len;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_rw = UIO_READ;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_td = curthread;
	uio.uio_resid = len;
	flags = wait ? 0 : MSG_DONTWAIT;
	error = soreceive(softc->ha_so, NULL, &uio, NULL, NULL, &flags);
	if (error == 0)
		return (CTL_HA_STATUS_SUCCESS);

	/* Consider all errors fatal for HA sanity. */
	mtx_lock(&softc->ha_lock);
	if (softc->ha_connected) {
		softc->ha_disconnect = 1;
		softc->ha_wakeup = 1;
		wakeup(&softc->ha_wakeup);
	}
	mtx_unlock(&softc->ha_lock);
	return (CTL_HA_STATUS_ERROR);
}