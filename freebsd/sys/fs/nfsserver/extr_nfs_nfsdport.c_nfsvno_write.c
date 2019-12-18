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
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/  uio_offset; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsheur {int nh_seqcount; int /*<<< orphan*/  nh_nextoff; } ;
struct mbuf {int m_len; struct mbuf* m_next; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int* srvbytes; } ;

/* Variables and functions */
 int ENOENT ; 
 int IO_NODELOCKED ; 
 int IO_SEQSHIFT ; 
 int IO_SYNC ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSPROC_WRITEDS ; 
 int /*<<< orphan*/  NFSUIOPROC (struct uio*,struct thread*) ; 
 size_t NFSV4OP_WRITE ; 
 int NFSWRITE_FILESYNC ; 
 int NFSWRITE_UNSTABLE ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int VOP_WRITE (struct vnode*,struct uio*,int,struct ucred*) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 char* mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int nfsrv_proxyds (struct vnode*,int /*<<< orphan*/ ,int,struct ucred*,struct thread*,int /*<<< orphan*/ ,struct mbuf**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfsheur* nfsrv_sequential_heuristic (struct uio*,struct vnode*) ; 
 TYPE_1__ nfsstatsv1 ; 
 int /*<<< orphan*/  panic (char*) ; 

int
nfsvno_write(struct vnode *vp, off_t off, int retlen, int cnt, int *stable,
    struct mbuf *mp, char *cp, struct ucred *cred, struct thread *p)
{
	struct iovec *ivp;
	int i, len;
	struct iovec *iv;
	int ioflags, error;
	struct uio io, *uiop = &io;
	struct nfsheur *nh;

	/*
	 * Attempt to write to a DS file. A return of ENOENT implies
	 * there is no DS file to write.
	 */
	error = nfsrv_proxyds(vp, off, retlen, cred, p, NFSPROC_WRITEDS,
	    &mp, cp, NULL, NULL, NULL);
	if (error != ENOENT) {
		*stable = NFSWRITE_FILESYNC;
		return (error);
	}

	ivp = malloc(cnt * sizeof (struct iovec), M_TEMP,
	    M_WAITOK);
	uiop->uio_iov = iv = ivp;
	uiop->uio_iovcnt = cnt;
	i = mtod(mp, caddr_t) + mp->m_len - cp;
	len = retlen;
	while (len > 0) {
		if (mp == NULL)
			panic("nfsvno_write");
		if (i > 0) {
			i = min(i, len);
			ivp->iov_base = cp;
			ivp->iov_len = i;
			ivp++;
			len -= i;
		}
		mp = mp->m_next;
		if (mp) {
			i = mp->m_len;
			cp = mtod(mp, caddr_t);
		}
	}

	if (*stable == NFSWRITE_UNSTABLE)
		ioflags = IO_NODELOCKED;
	else
		ioflags = (IO_SYNC | IO_NODELOCKED);
	uiop->uio_resid = retlen;
	uiop->uio_rw = UIO_WRITE;
	uiop->uio_segflg = UIO_SYSSPACE;
	NFSUIOPROC(uiop, p);
	uiop->uio_offset = off;
	nh = nfsrv_sequential_heuristic(uiop, vp);
	ioflags |= nh->nh_seqcount << IO_SEQSHIFT;
	/* XXX KDM make this more systematic? */
	nfsstatsv1.srvbytes[NFSV4OP_WRITE] += uiop->uio_resid;
	error = VOP_WRITE(vp, uiop, ioflags, cred);
	if (error == 0)
		nh->nh_nextoff = uiop->uio_offset;
	free(iv, M_TEMP);

	NFSEXITCODE(error);
	return (error);
}