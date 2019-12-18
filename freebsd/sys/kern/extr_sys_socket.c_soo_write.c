#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uio {TYPE_1__* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct socket {int so_options; } ;
struct file {struct socket* f_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int SO_NOSIGPIPE ; 
 int mac_socket_check_send (struct ucred*,struct socket*) ; 
 int sosend (struct socket*,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tdsignal (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
soo_write(struct file *fp, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{
	struct socket *so = fp->f_data;
	int error;

#ifdef MAC
	error = mac_socket_check_send(active_cred, so);
	if (error)
		return (error);
#endif
	error = sosend(so, 0, uio, 0, 0, 0, uio->uio_td);
	if (error == EPIPE && (so->so_options & SO_NOSIGPIPE) == 0) {
		PROC_LOCK(uio->uio_td->td_proc);
		tdsignal(uio->uio_td, SIGPIPE);
		PROC_UNLOCK(uio->uio_td->td_proc);
	}
	return (error);
}