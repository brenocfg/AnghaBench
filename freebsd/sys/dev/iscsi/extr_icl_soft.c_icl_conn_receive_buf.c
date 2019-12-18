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
typedef  int /*<<< orphan*/  uio ;
struct uio {int uio_iovcnt; size_t uio_resid; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct socket {int dummy; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct icl_conn {struct socket* ic_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_DEBUG (char*,...) ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  memset (struct uio*,int /*<<< orphan*/ ,int) ; 
 int soreceive (struct socket*,int /*<<< orphan*/ *,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
icl_conn_receive_buf(struct icl_conn *ic, void *buf, size_t len)
{
	struct iovec iov[1];
	struct uio uio;
	struct socket *so;
	int error, flags;

	so = ic->ic_socket;

	memset(&uio, 0, sizeof(uio));
	iov[0].iov_base = buf;
	iov[0].iov_len = len;
	uio.uio_iov = iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = 0;
	uio.uio_resid = len;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_rw = UIO_READ;

	flags = MSG_DONTWAIT;
	error = soreceive(so, NULL, &uio, NULL, NULL, &flags);
	if (error != 0) {
		ICL_DEBUG("soreceive error %d", error);
		return (-1);
	}
	if (uio.uio_resid != 0) {
		ICL_DEBUG("short read");
		return (-1);
	}

	return (0);
}