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
struct uio {scalar_t__ uio_offset; void* uio_resid; void* iov_len; int /*<<< orphan*/  uio_segflg; struct uio* uio_iov; } ;
struct timeval {int dummy; } ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct kttcp_io_args {unsigned long long kio_totalsize; unsigned long long kio_bytesdone; int /*<<< orphan*/  kio_elapsed; int /*<<< orphan*/  kio_socket; } ;
struct iovec {scalar_t__ uio_offset; void* uio_resid; void* iov_len; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct file {int f_flag; scalar_t__ f_type; scalar_t__ f_data; } ;
typedef  int /*<<< orphan*/  auio ;
typedef  int /*<<< orphan*/  aiov ;

/* Variables and functions */
 scalar_t__ DTYPE_SOCKET ; 
 int EBADF ; 
 int EFTYPE ; 
 int FWRITE ; 
 void* MIN (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  UIO_NOCOPY ; 
 int /*<<< orphan*/  bzero (struct uio*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,struct file**) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 void* nbyte ; 
 int sosend (struct socket*,int /*<<< orphan*/ *,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kttcp_send(struct thread *td, struct kttcp_io_args *kio)
{
	struct file *fp;
	int error;
	struct timeval t0, t1;
	unsigned long long len = 0;
	struct uio auio;
	struct iovec aiov;

	bzero(&aiov, sizeof(aiov));
	bzero(&auio, sizeof(auio));
	auio.uio_iov = &aiov;
	auio.uio_segflg = UIO_NOCOPY;

	error = fget(td, kio->kio_socket, &fp);
	if (error != 0)
		return error;

	if ((fp->f_flag & FWRITE) == 0) {
		fdrop(fp, td);
		return EBADF;
	}
	if (fp->f_type == DTYPE_SOCKET) {
		len = kio->kio_totalsize;
		microtime(&t0);
		do {
			nbyte =  MIN(len, (unsigned long long)nbyte);
			aiov.iov_len = nbyte;
			auio.uio_resid = nbyte;
			auio.uio_offset = 0;
			error = sosend((struct socket *)fp->f_data, NULL,
				       &auio, NULL, NULL, 0, td);
			len -= auio.uio_offset;
		} while (error == 0 && len != 0);
		microtime(&t1);
	} else
		error = EFTYPE;
	fdrop(fp, td);
	if (error != 0)
		return error;
	timersub(&t1, &t0, &kio->kio_elapsed);

	kio->kio_bytesdone = kio->kio_totalsize - len;

	return 0;
}