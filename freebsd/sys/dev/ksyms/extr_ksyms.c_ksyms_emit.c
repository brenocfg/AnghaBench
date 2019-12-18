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
struct uio {int uio_iovcnt; int /*<<< orphan*/  uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_resid; int /*<<< orphan*/  uio_offset; struct iovec* uio_iov; } ;
struct ksyms_softc {int /*<<< orphan*/  sc_objsz; int /*<<< orphan*/  sc_obj; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  curthread ; 
 int uiomove_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
ksyms_emit(struct ksyms_softc *sc, void *buf, off_t off, size_t sz)
{
	struct iovec iov;
	struct uio uio;

	iov.iov_base = buf;
	iov.iov_len = sz;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = off;
	uio.uio_resid = (ssize_t)sz;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_rw = UIO_WRITE;
	uio.uio_td = curthread;

	return (uiomove_object(sc->sc_obj, sc->sc_objsz, &uio));
}