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
struct uio {int uio_iovcnt; size_t uio_resid; scalar_t__ uio_offset; int /*<<< orphan*/  uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
struct filemon {int error; int /*<<< orphan*/  cred; TYPE_1__* fp; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ f_type; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int /*<<< orphan*/  curthread ; 
 int fo_write (TYPE_1__*,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filemon_output(struct filemon *filemon, char *msg, size_t len)
{
	struct uio auio;
	struct iovec aiov;
	int error;

	if (filemon->fp == NULL)
		return;

	aiov.iov_base = msg;
	aiov.iov_len = len;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_resid = len;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = UIO_WRITE;
	auio.uio_td = curthread;
	auio.uio_offset = (off_t) -1;

	if (filemon->fp->f_type == DTYPE_VNODE)
		bwillwrite();

	error = fo_write(filemon->fp, &auio, filemon->cred, 0, curthread);
	if (error != 0 && filemon->error == 0)
		filemon->error = error;
}