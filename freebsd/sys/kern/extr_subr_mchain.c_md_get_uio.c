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
struct uio {scalar_t__ uio_segflg; scalar_t__ uio_iovcnt; long uio_offset; TYPE_1__* uio_iov; scalar_t__ uio_resid; } ;
struct mdchain {int dummy; } ;
struct TYPE_2__ {long iov_len; char* iov_base; } ;

/* Variables and functions */
 int EFBIG ; 
 int MB_MSYSTEM ; 
 int MB_MUSER ; 
 scalar_t__ UIO_SYSSPACE ; 
 int md_get_mem (struct mdchain*,char*,long,int) ; 

int
md_get_uio(struct mdchain *mdp, struct uio *uiop, int size)
{
	char *uiocp;
	long left;
	int mtype, error;

	mtype = (uiop->uio_segflg == UIO_SYSSPACE) ? MB_MSYSTEM : MB_MUSER;
	while (size > 0 && uiop->uio_resid) {
		if (uiop->uio_iovcnt <= 0 || uiop->uio_iov == NULL)
			return (EFBIG);
		left = uiop->uio_iov->iov_len;
		if (left == 0) {
			uiop->uio_iov++;
			uiop->uio_iovcnt--;
			continue;
		}
		uiocp = uiop->uio_iov->iov_base;
		if (left > size)
			left = size;
		error = md_get_mem(mdp, uiocp, left, mtype);
		if (error)
			return (error);
		uiop->uio_offset += left;
		uiop->uio_resid -= left;
		uiop->uio_iov->iov_base =
		    (char *)uiop->uio_iov->iov_base + left;
		uiop->uio_iov->iov_len -= left;
		size -= left;
	}
	return (0);
}