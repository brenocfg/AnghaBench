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
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/ * uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mbuf {int m_len; struct mbuf* m_next; } ;
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int MLEN ; 
 int M_SIZE (struct mbuf*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSMGET (struct mbuf*) ; 
 int NFSM_RNDUP (int) ; 
 int NFS_MAXPATHLEN ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READLINK (struct vnode*,struct uio*,struct ucred*) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_adj (struct mbuf*,int,int) ; 

int
nfsvno_readlink(struct vnode *vp, struct ucred *cred, struct thread *p,
    struct mbuf **mpp, struct mbuf **mpendp, int *lenp)
{
	struct iovec iv[(NFS_MAXPATHLEN+MLEN-1)/MLEN];
	struct iovec *ivp = iv;
	struct uio io, *uiop = &io;
	struct mbuf *mp, *mp2 = NULL, *mp3 = NULL;
	int i, len, tlen, error = 0;

	len = 0;
	i = 0;
	while (len < NFS_MAXPATHLEN) {
		NFSMGET(mp);
		MCLGET(mp, M_WAITOK);
		mp->m_len = M_SIZE(mp);
		if (len == 0) {
			mp3 = mp2 = mp;
		} else {
			mp2->m_next = mp;
			mp2 = mp;
		}
		if ((len + mp->m_len) > NFS_MAXPATHLEN) {
			mp->m_len = NFS_MAXPATHLEN - len;
			len = NFS_MAXPATHLEN;
		} else {
			len += mp->m_len;
		}
		ivp->iov_base = mtod(mp, caddr_t);
		ivp->iov_len = mp->m_len;
		i++;
		ivp++;
	}
	uiop->uio_iov = iv;
	uiop->uio_iovcnt = i;
	uiop->uio_offset = 0;
	uiop->uio_resid = len;
	uiop->uio_rw = UIO_READ;
	uiop->uio_segflg = UIO_SYSSPACE;
	uiop->uio_td = NULL;
	error = VOP_READLINK(vp, uiop, cred);
	if (error) {
		m_freem(mp3);
		*lenp = 0;
		goto out;
	}
	if (uiop->uio_resid > 0) {
		len -= uiop->uio_resid;
		tlen = NFSM_RNDUP(len);
		nfsrv_adj(mp3, NFS_MAXPATHLEN - tlen, tlen - len);
	}
	*lenp = len;
	*mpp = mp3;
	*mpendp = mp;

out:
	NFSEXITCODE(error);
	return (error);
}