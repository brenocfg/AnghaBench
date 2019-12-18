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
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/  uio_offset; int /*<<< orphan*/ * uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsheur {int nh_seqcount; int /*<<< orphan*/  nh_nextoff; } ;
struct mbuf {struct mbuf* m_next; scalar_t__ m_len; } ;
struct iovec {int iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int* srvbytes; } ;

/* Variables and functions */
 int ENOENT ; 
 int IO_NODELOCKED ; 
 int IO_SEQSHIFT ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSMGET (struct mbuf*) ; 
 int NFSM_RNDUP (int) ; 
 int /*<<< orphan*/  NFSPROC_READDS ; 
 size_t NFSV4OP_READ ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READ (struct vnode*,struct uio*,int,struct ucred*) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct iovec* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_adj (struct mbuf*,int,int) ; 
 int nfsrv_proxyds (struct vnode*,int /*<<< orphan*/ ,int,struct ucred*,struct thread*,int /*<<< orphan*/ ,struct mbuf**,int /*<<< orphan*/ *,struct mbuf**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfsheur* nfsrv_sequential_heuristic (struct uio*,struct vnode*) ; 
 TYPE_1__ nfsstatsv1 ; 
 int /*<<< orphan*/  panic (char*) ; 

int
nfsvno_read(struct vnode *vp, off_t off, int cnt, struct ucred *cred,
    struct thread *p, struct mbuf **mpp, struct mbuf **mpendp)
{
	struct mbuf *m;
	int i;
	struct iovec *iv;
	struct iovec *iv2;
	int error = 0, len, left, siz, tlen, ioflag = 0;
	struct mbuf *m2 = NULL, *m3;
	struct uio io, *uiop = &io;
	struct nfsheur *nh;

	/*
	 * Attempt to read from a DS file. A return of ENOENT implies
	 * there is no DS file to read.
	 */
	error = nfsrv_proxyds(vp, off, cnt, cred, p, NFSPROC_READDS, mpp,
	    NULL, mpendp, NULL, NULL);
	if (error != ENOENT)
		return (error);

	len = left = NFSM_RNDUP(cnt);
	m3 = NULL;
	/*
	 * Generate the mbuf list with the uio_iov ref. to it.
	 */
	i = 0;
	while (left > 0) {
		NFSMGET(m);
		MCLGET(m, M_WAITOK);
		m->m_len = 0;
		siz = min(M_TRAILINGSPACE(m), left);
		left -= siz;
		i++;
		if (m3)
			m2->m_next = m;
		else
			m3 = m;
		m2 = m;
	}
	iv = malloc(i * sizeof (struct iovec),
	    M_TEMP, M_WAITOK);
	uiop->uio_iov = iv2 = iv;
	m = m3;
	left = len;
	i = 0;
	while (left > 0) {
		if (m == NULL)
			panic("nfsvno_read iov");
		siz = min(M_TRAILINGSPACE(m), left);
		if (siz > 0) {
			iv->iov_base = mtod(m, caddr_t) + m->m_len;
			iv->iov_len = siz;
			m->m_len += siz;
			left -= siz;
			iv++;
			i++;
		}
		m = m->m_next;
	}
	uiop->uio_iovcnt = i;
	uiop->uio_offset = off;
	uiop->uio_resid = len;
	uiop->uio_rw = UIO_READ;
	uiop->uio_segflg = UIO_SYSSPACE;
	uiop->uio_td = NULL;
	nh = nfsrv_sequential_heuristic(uiop, vp);
	ioflag |= nh->nh_seqcount << IO_SEQSHIFT;
	/* XXX KDM make this more systematic? */
	nfsstatsv1.srvbytes[NFSV4OP_READ] += uiop->uio_resid;
	error = VOP_READ(vp, uiop, IO_NODELOCKED | ioflag, cred);
	free(iv2, M_TEMP);
	if (error) {
		m_freem(m3);
		*mpp = NULL;
		goto out;
	}
	nh->nh_nextoff = uiop->uio_offset;
	tlen = len - uiop->uio_resid;
	cnt = cnt < tlen ? cnt : tlen;
	tlen = NFSM_RNDUP(cnt);
	if (tlen == 0) {
		m_freem(m3);
		m3 = NULL;
	} else if (len != tlen || tlen != cnt)
		nfsrv_adj(m3, len - tlen, tlen - cnt);
	*mpp = m3;
	*mpendp = m2;

out:
	NFSEXITCODE(error);
	return (error);
}