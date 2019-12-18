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
struct uio {int uio_iovcnt; scalar_t__ uio_segflg; int uio_offset; int uio_resid; TYPE_1__* uio_iov; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int iov_len; char* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSBCOPY (char*,char*,int) ; 
 int /*<<< orphan*/  NFSMCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSMGET (struct mbuf*) ; 
 char* NFSMTOD (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_SYSSPACE ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  copyin (char*,char*,int) ; 
 int mbuf_len (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_setlen (struct mbuf*,int) ; 
 int /*<<< orphan*/  mbuf_setnext (struct mbuf*,struct mbuf*) ; 
 int ncl_mbuf_mlen ; 

struct mbuf *
nfsm_uiombuflist(struct uio *uiop, int siz, struct mbuf **mbp, char **cpp)
{
	char *uiocp;
	struct mbuf *mp, *mp2, *firstmp;
	int xfer, left, mlen;
	int uiosiz, clflg;
	char *tcp;

	KASSERT(uiop->uio_iovcnt == 1, ("nfsm_uiotombuf: iovcnt != 1"));

	if (siz > ncl_mbuf_mlen)	/* or should it >= MCLBYTES ?? */
		clflg = 1;
	else
		clflg = 0;
	if (clflg != 0)
		NFSMCLGET(mp, M_WAITOK);
	else
		NFSMGET(mp);
	mbuf_setlen(mp, 0);
	firstmp = mp2 = mp;
	while (siz > 0) {
		left = uiop->uio_iov->iov_len;
		uiocp = uiop->uio_iov->iov_base;
		if (left > siz)
			left = siz;
		uiosiz = left;
		while (left > 0) {
			mlen = M_TRAILINGSPACE(mp);
			if (mlen == 0) {
				if (clflg)
					NFSMCLGET(mp, M_WAITOK);
				else
					NFSMGET(mp);
				mbuf_setlen(mp, 0);
				mbuf_setnext(mp2, mp);
				mp2 = mp;
				mlen = M_TRAILINGSPACE(mp);
			}
			xfer = (left > mlen) ? mlen : left;
			if (uiop->uio_segflg == UIO_SYSSPACE)
				NFSBCOPY(uiocp, NFSMTOD(mp, caddr_t) +
				    mbuf_len(mp), xfer);
			else
				copyin(uiocp, NFSMTOD(mp, caddr_t) +
				    mbuf_len(mp), xfer);
			mbuf_setlen(mp, mbuf_len(mp) + xfer);
			left -= xfer;
			uiocp += xfer;
			uiop->uio_offset += xfer;
			uiop->uio_resid -= xfer;
		}
		tcp = (char *)uiop->uio_iov->iov_base;
		tcp += uiosiz;
		uiop->uio_iov->iov_base = (void *)tcp;
		uiop->uio_iov->iov_len -= uiosiz;
		siz -= uiosiz;
	}
	if (cpp != NULL)
		*cpp = NFSMTOD(mp, caddr_t) + mbuf_len(mp);
	if (mbp != NULL)
		*mbp = mp;
	return (firstmp);
}