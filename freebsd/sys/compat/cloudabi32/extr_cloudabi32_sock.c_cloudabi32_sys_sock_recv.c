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
struct cloudabi32_sys_sock_recv_args {int /*<<< orphan*/  out; int /*<<< orphan*/  sock; TYPE_2__ const* in; } ;
typedef  int /*<<< orphan*/  ro ;
typedef  int /*<<< orphan*/  ri ;
typedef  int /*<<< orphan*/  iovobj ;
struct TYPE_7__ {size_t ro_datalen; size_t ro_fdslen; int /*<<< orphan*/  ro_flags; } ;
typedef  TYPE_1__ cloudabi32_recv_out_t ;
struct TYPE_8__ {size_t ri_data_len; int /*<<< orphan*/  ri_flags; int /*<<< orphan*/  ri_fds_len; int /*<<< orphan*/  ri_fds; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf; int /*<<< orphan*/  ri_data; } ;
typedef  TYPE_2__ cloudabi32_recv_in_t ;
typedef  TYPE_2__ cloudabi32_iovec_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_SOCKET ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* TO_PTR (int /*<<< orphan*/ ) ; 
 size_t UIO_MAXIOV ; 
 int cloudabi_sock_recv (struct thread*,int /*<<< orphan*/ ,struct iovec*,size_t,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int copyin (TYPE_2__ const*,TYPE_2__*,int) ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* mallocarray (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi32_sys_sock_recv(struct thread *td,
    struct cloudabi32_sys_sock_recv_args *uap)
{
	cloudabi32_recv_in_t ri;
	cloudabi32_recv_out_t ro = {};
	cloudabi32_iovec_t iovobj;
	struct iovec *iov;
	const cloudabi32_iovec_t *user_iov;
	size_t i, rdatalen, rfdslen;
	int error;

	error = copyin(uap->in, &ri, sizeof(ri));
	if (error != 0)
		return (error);

	/* Convert iovecs to native format. */
	if (ri.ri_data_len > UIO_MAXIOV)
		return (EINVAL);
	iov = mallocarray(ri.ri_data_len, sizeof(struct iovec),
	    M_SOCKET, M_WAITOK);
	user_iov = TO_PTR(ri.ri_data);
	for (i = 0; i < ri.ri_data_len; i++) {
		error = copyin(&user_iov[i], &iovobj, sizeof(iovobj));
		if (error != 0) {
			free(iov, M_SOCKET);
			return (error);
		}
		iov[i].iov_base = TO_PTR(iovobj.buf);
		iov[i].iov_len = iovobj.buf_len;
	}

	error = cloudabi_sock_recv(td, uap->sock, iov, ri.ri_data_len,
	    TO_PTR(ri.ri_fds), ri.ri_fds_len, ri.ri_flags, &rdatalen,
	    &rfdslen, &ro.ro_flags);
	free(iov, M_SOCKET);
	if (error != 0)
		return (error);

	ro.ro_datalen = rdatalen;
	ro.ro_fdslen = rfdslen;
	return (copyout(&ro, uap->out, sizeof(ro)));
}