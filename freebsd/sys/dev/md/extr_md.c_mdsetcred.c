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
struct uio {int uio_iovcnt; int /*<<< orphan*/  uio_resid; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ucred {int dummy; } ;
struct md_s {scalar_t__ vnode; scalar_t__ cred; int /*<<< orphan*/  sectorsize; } ;
struct iovec {char* iov_base; int /*<<< orphan*/  iov_len; } ;
typedef  int /*<<< orphan*/  auio ;

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READ (scalar_t__,struct uio*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VOP_UNLOCK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct uio*,int) ; 
 int /*<<< orphan*/  crfree (scalar_t__) ; 
 scalar_t__ crhold (struct ucred*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (scalar_t__,int) ; 

__attribute__((used)) static int
mdsetcred(struct md_s *sc, struct ucred *cred)
{
	char *tmpbuf;
	int error = 0;

	/*
	 * Set credits in our softc
	 */

	if (sc->cred)
		crfree(sc->cred);
	sc->cred = crhold(cred);

	/*
	 * Horrible kludge to establish credentials for NFS  XXX.
	 */

	if (sc->vnode) {
		struct uio auio;
		struct iovec aiov;

		tmpbuf = malloc(sc->sectorsize, M_TEMP, M_WAITOK);
		bzero(&auio, sizeof(auio));

		aiov.iov_base = tmpbuf;
		aiov.iov_len = sc->sectorsize;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_SYSSPACE;
		auio.uio_resid = aiov.iov_len;
		vn_lock(sc->vnode, LK_EXCLUSIVE | LK_RETRY);
		error = VOP_READ(sc->vnode, &auio, 0, sc->cred);
		VOP_UNLOCK(sc->vnode, 0);
		free(tmpbuf, M_TEMP);
	}
	return (error);
}