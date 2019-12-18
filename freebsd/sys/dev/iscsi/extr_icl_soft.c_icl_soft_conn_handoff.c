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
struct socket {scalar_t__ so_type; } ;
struct icl_conn {struct socket* ic_socket; } ;
struct file {scalar_t__ f_type; struct socket* f_data; int /*<<< orphan*/ * f_ops; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SOCK_CLIENT ; 
 scalar_t__ DTYPE_SOCKET ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_LOCK_ASSERT_NOT (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_WARN (char*) ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdrop (struct file*,int /*<<< orphan*/ ) ; 
 int fget (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct file**) ; 
 int icl_conn_start (struct icl_conn*) ; 

int
icl_soft_conn_handoff(struct icl_conn *ic, int fd)
{
	struct file *fp;
	struct socket *so;
	cap_rights_t rights;
	int error;

	ICL_CONN_LOCK_ASSERT_NOT(ic);

#ifdef ICL_KERNEL_PROXY
	/*
	 * We're transitioning to Full Feature phase, and we don't
	 * really care.
	 */
	if (fd == 0) {
		ICL_CONN_LOCK(ic);
		if (ic->ic_socket == NULL) {
			ICL_CONN_UNLOCK(ic);
			ICL_WARN("proxy handoff without connect"); 
			return (EINVAL);
		}
		ICL_CONN_UNLOCK(ic);
		return (0);
	}
#endif

	/*
	 * Steal the socket from userland.
	 */
	error = fget(curthread, fd,
	    cap_rights_init(&rights, CAP_SOCK_CLIENT), &fp);
	if (error != 0)
		return (error);
	if (fp->f_type != DTYPE_SOCKET) {
		fdrop(fp, curthread);
		return (EINVAL);
	}
	so = fp->f_data;
	if (so->so_type != SOCK_STREAM) {
		fdrop(fp, curthread);
		return (EINVAL);
	}

	ICL_CONN_LOCK(ic);

	if (ic->ic_socket != NULL) {
		ICL_CONN_UNLOCK(ic);
		fdrop(fp, curthread);
		return (EBUSY);
	}

	ic->ic_socket = fp->f_data;
	fp->f_ops = &badfileops;
	fp->f_data = NULL;
	fdrop(fp, curthread);
	ICL_CONN_UNLOCK(ic);

	error = icl_conn_start(ic);

	return (error);
}