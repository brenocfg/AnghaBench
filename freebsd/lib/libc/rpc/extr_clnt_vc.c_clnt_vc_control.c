#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct timeval {int dummy; } ;
struct netbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  ct_mcallc; int /*<<< orphan*/  ct_mcalli; } ;
struct ct_data {size_t ct_fd; TYPE_1__ ct_u; struct netbuf ct_addr; struct timeval ct_wait; void* ct_waitset; void* ct_closeit; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  void* bool_t ;
struct TYPE_5__ {scalar_t__ cl_private; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int BYTES_PER_XDR_UNIT ; 
#define  CLGET_FD 141 
#define  CLGET_PROG 140 
#define  CLGET_SERVER_ADDR 139 
#define  CLGET_SVC_ADDR 138 
#define  CLGET_TIMEOUT 137 
#define  CLGET_VERS 136 
#define  CLGET_XID 135 
#define  CLSET_FD_CLOSE 134 
#define  CLSET_FD_NCLOSE 133 
#define  CLSET_PROG 132 
#define  CLSET_SVC_ADDR 131 
#define  CLSET_TIMEOUT 130 
#define  CLSET_VERS 129 
#define  CLSET_XID 128 
 void* FALSE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 void* TRUE ; 
 scalar_t__ __isthreaded ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_fd_lock ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonlp (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohlp (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_fd_lock (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr_sigsetmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_not_ok (struct timeval*) ; 
 int /*<<< orphan*/ * vc_cv ; 
 int* vc_fd_locks ; 

__attribute__((used)) static bool_t
clnt_vc_control(CLIENT *cl, u_int request, void *info)
{
	struct ct_data *ct;
	void *infop = info;
	sigset_t mask;
	sigset_t newmask;
	int rpc_lock_value;

	assert(cl != NULL);

	ct = (struct ct_data *)cl->cl_private;

	sigfillset(&newmask);
	thr_sigsetmask(SIG_SETMASK, &newmask, &mask);
	mutex_lock(&clnt_fd_lock);
	while (vc_fd_locks[ct->ct_fd])
		cond_wait(&vc_cv[ct->ct_fd], &clnt_fd_lock);
	if (__isthreaded)
                rpc_lock_value = 1;
        else
                rpc_lock_value = 0;
	vc_fd_locks[ct->ct_fd] = rpc_lock_value;
	mutex_unlock(&clnt_fd_lock);

	switch (request) {
	case CLSET_FD_CLOSE:
		ct->ct_closeit = TRUE;
		release_fd_lock(ct->ct_fd, mask);
		return (TRUE);
	case CLSET_FD_NCLOSE:
		ct->ct_closeit = FALSE;
		release_fd_lock(ct->ct_fd, mask);
		return (TRUE);
	default:
		break;
	}

	/* for other requests which use info */
	if (info == NULL) {
		release_fd_lock(ct->ct_fd, mask);
		return (FALSE);
	}
	switch (request) {
	case CLSET_TIMEOUT:
		if (time_not_ok((struct timeval *)info)) {
			release_fd_lock(ct->ct_fd, mask);
			return (FALSE);
		}
		ct->ct_wait = *(struct timeval *)infop;
		ct->ct_waitset = TRUE;
		break;
	case CLGET_TIMEOUT:
		*(struct timeval *)infop = ct->ct_wait;
		break;
	case CLGET_SERVER_ADDR:
		(void) memcpy(info, ct->ct_addr.buf, (size_t)ct->ct_addr.len);
		break;
	case CLGET_FD:
		*(int *)info = ct->ct_fd;
		break;
	case CLGET_SVC_ADDR:
		/* The caller should not free this memory area */
		*(struct netbuf *)info = ct->ct_addr;
		break;
	case CLSET_SVC_ADDR:		/* set to new address */
		release_fd_lock(ct->ct_fd, mask);
		return (FALSE);
	case CLGET_XID:
		/*
		 * use the knowledge that xid is the
		 * first element in the call structure
		 * This will get the xid of the PREVIOUS call
		 */
		ntohlp(info, &ct->ct_u.ct_mcalli);
		break;
	case CLSET_XID:
		/* This will set the xid of the NEXT call */
		/* increment by 1 as clnt_vc_call() decrements once */
		htonlp(&ct->ct_u.ct_mcalli, info, 1);
		break;
	case CLGET_VERS:
		/*
		 * This RELIES on the information that, in the call body,
		 * the version number field is the fifth field from the
		 * beginning of the RPC header. MUST be changed if the
		 * call_struct is changed
		 */
		ntohlp(info, ct->ct_u.ct_mcallc + 4 * BYTES_PER_XDR_UNIT);
		break;

	case CLSET_VERS:
		htonlp(ct->ct_u.ct_mcallc + 4 * BYTES_PER_XDR_UNIT, info, 0);
		break;

	case CLGET_PROG:
		/*
		 * This RELIES on the information that, in the call body,
		 * the program number field is the fourth field from the
		 * beginning of the RPC header. MUST be changed if the
		 * call_struct is changed
		 */
		ntohlp(info, ct->ct_u.ct_mcallc + 3 * BYTES_PER_XDR_UNIT);
		break;

	case CLSET_PROG:
		htonlp(ct->ct_u.ct_mcallc + 3 * BYTES_PER_XDR_UNIT, info, 0);
		break;

	default:
		release_fd_lock(ct->ct_fd, mask);
		return (FALSE);
	}
	release_fd_lock(ct->ct_fd, mask);
	return (TRUE);
}