#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct iovec {int /*<<< orphan*/  iov_len; void* iov_base; } ;
struct cloudabi32_sys_sock_send_args {int /*<<< orphan*/  out; int /*<<< orphan*/  sock; TYPE_2__ const* in; } ;
typedef  int /*<<< orphan*/  so ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  iovobj ;
struct TYPE_7__ {size_t so_datalen; } ;
typedef  TYPE_1__ cloudabi32_send_out_t ;
struct TYPE_8__ {size_t si_data_len; int /*<<< orphan*/  si_fds_len; int /*<<< orphan*/  si_fds; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf; int /*<<< orphan*/  si_data; } ;
typedef  TYPE_2__ cloudabi32_send_in_t ;
typedef  TYPE_2__ cloudabi32_ciovec_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_SOCKET ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* TO_PTR (int /*<<< orphan*/ ) ; 
 size_t UIO_MAXIOV ; 
 int cloudabi_sock_send (struct thread*,int /*<<< orphan*/ ,struct iovec*,size_t,void*,int /*<<< orphan*/ ,size_t*) ; 
 int copyin (TYPE_2__ const*,TYPE_2__*,int) ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* mallocarray (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi32_sys_sock_send(struct thread *td,
    struct cloudabi32_sys_sock_send_args *uap)
{
	cloudabi32_send_in_t si;
	cloudabi32_send_out_t so = {};
	cloudabi32_ciovec_t iovobj;
	struct iovec *iov;
	const cloudabi32_ciovec_t *user_iov;
	size_t datalen, i;
	int error;

	error = copyin(uap->in, &si, sizeof(si));
	if (error != 0)
		return (error);

	/* Convert iovecs to native format. */
	if (si.si_data_len > UIO_MAXIOV)
		return (EINVAL);
	iov = mallocarray(si.si_data_len, sizeof(struct iovec),
	    M_SOCKET, M_WAITOK);
	user_iov = TO_PTR(si.si_data);
	for (i = 0; i < si.si_data_len; i++) {
		error = copyin(&user_iov[i], &iovobj, sizeof(iovobj));
		if (error != 0) {
			free(iov, M_SOCKET);
			return (error);
		}
		iov[i].iov_base = TO_PTR(iovobj.buf);
		iov[i].iov_len = iovobj.buf_len;
	}

	error = cloudabi_sock_send(td, uap->sock, iov, si.si_data_len,
	    TO_PTR(si.si_fds), si.si_fds_len, &datalen);
	free(iov, M_SOCKET);
	if (error != 0)
		return (error);

	so.so_datalen = datalen;
	return (copyout(&so, uap->out, sizeof(so)));
}