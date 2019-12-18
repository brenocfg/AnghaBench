#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct timeval {int dummy; } ;
struct TYPE_7__ {size_t ss_len; } ;
struct ct_data {char const* ct_waitchan; int /*<<< orphan*/  ct_lock; TYPE_1__* ct_backchannelxprt; int /*<<< orphan*/  ct_waitflag; int /*<<< orphan*/  ct_mcallc; int /*<<< orphan*/  ct_xid; TYPE_3__ ct_addr; struct timeval ct_wait; void* ct_closeit; } ;
typedef  void* bool_t ;
struct TYPE_6__ {scalar_t__ cl_private; } ;
struct TYPE_5__ {struct ct_data* xp_p2; } ;
typedef  TYPE_1__ SVCXPRT ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int BYTES_PER_XDR_UNIT ; 
#define  CLGET_INTERRUPTIBLE 145 
#define  CLGET_PROG 144 
#define  CLGET_SERVER_ADDR 143 
#define  CLGET_SVC_ADDR 142 
#define  CLGET_TIMEOUT 141 
#define  CLGET_VERS 140 
#define  CLGET_WAITCHAN 139 
#define  CLGET_XID 138 
#define  CLSET_BACKCHANNEL 137 
#define  CLSET_FD_CLOSE 136 
#define  CLSET_FD_NCLOSE 135 
#define  CLSET_INTERRUPTIBLE 134 
#define  CLSET_PROG 133 
#define  CLSET_SVC_ADDR 132 
#define  CLSET_TIMEOUT 131 
#define  CLSET_VERS 130 
#define  CLSET_WAITCHAN 129 
#define  CLSET_XID 128 
 void* FALSE ; 
 int /*<<< orphan*/  PCATCH ; 
 void* TRUE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_not_ok (struct timeval*) ; 

__attribute__((used)) static bool_t
clnt_vc_control(CLIENT *cl, u_int request, void *info)
{
	struct ct_data *ct = (struct ct_data *)cl->cl_private;
	void *infop = info;
	SVCXPRT *xprt;

	mtx_lock(&ct->ct_lock);

	switch (request) {
	case CLSET_FD_CLOSE:
		ct->ct_closeit = TRUE;
		mtx_unlock(&ct->ct_lock);
		return (TRUE);
	case CLSET_FD_NCLOSE:
		ct->ct_closeit = FALSE;
		mtx_unlock(&ct->ct_lock);
		return (TRUE);
	default:
		break;
	}

	/* for other requests which use info */
	if (info == NULL) {
		mtx_unlock(&ct->ct_lock);
		return (FALSE);
	}
	switch (request) {
	case CLSET_TIMEOUT:
		if (time_not_ok((struct timeval *)info)) {
			mtx_unlock(&ct->ct_lock);
			return (FALSE);
		}
		ct->ct_wait = *(struct timeval *)infop;
		break;
	case CLGET_TIMEOUT:
		*(struct timeval *)infop = ct->ct_wait;
		break;
	case CLGET_SERVER_ADDR:
		(void) memcpy(info, &ct->ct_addr, (size_t)ct->ct_addr.ss_len);
		break;
	case CLGET_SVC_ADDR:
		/*
		 * Slightly different semantics to userland - we use
		 * sockaddr instead of netbuf.
		 */
		memcpy(info, &ct->ct_addr, ct->ct_addr.ss_len);
		break;
	case CLSET_SVC_ADDR:		/* set to new address */
		mtx_unlock(&ct->ct_lock);
		return (FALSE);
	case CLGET_XID:
		*(uint32_t *)info = ct->ct_xid;
		break;
	case CLSET_XID:
		/* This will set the xid of the NEXT call */
		/* decrement by 1 as clnt_vc_call() increments once */
		ct->ct_xid = *(uint32_t *)info - 1;
		break;
	case CLGET_VERS:
		/*
		 * This RELIES on the information that, in the call body,
		 * the version number field is the fifth field from the
		 * beginning of the RPC header. MUST be changed if the
		 * call_struct is changed
		 */
		*(uint32_t *)info =
		    ntohl(*(uint32_t *)(void *)(ct->ct_mcallc +
		    4 * BYTES_PER_XDR_UNIT));
		break;

	case CLSET_VERS:
		*(uint32_t *)(void *)(ct->ct_mcallc +
		    4 * BYTES_PER_XDR_UNIT) =
		    htonl(*(uint32_t *)info);
		break;

	case CLGET_PROG:
		/*
		 * This RELIES on the information that, in the call body,
		 * the program number field is the fourth field from the
		 * beginning of the RPC header. MUST be changed if the
		 * call_struct is changed
		 */
		*(uint32_t *)info =
		    ntohl(*(uint32_t *)(void *)(ct->ct_mcallc +
		    3 * BYTES_PER_XDR_UNIT));
		break;

	case CLSET_PROG:
		*(uint32_t *)(void *)(ct->ct_mcallc +
		    3 * BYTES_PER_XDR_UNIT) =
		    htonl(*(uint32_t *)info);
		break;

	case CLSET_WAITCHAN:
		ct->ct_waitchan = (const char *)info;
		break;

	case CLGET_WAITCHAN:
		*(const char **) info = ct->ct_waitchan;
		break;

	case CLSET_INTERRUPTIBLE:
		if (*(int *) info)
			ct->ct_waitflag = PCATCH;
		else
			ct->ct_waitflag = 0;
		break;

	case CLGET_INTERRUPTIBLE:
		if (ct->ct_waitflag)
			*(int *) info = TRUE;
		else
			*(int *) info = FALSE;
		break;

	case CLSET_BACKCHANNEL:
		xprt = (SVCXPRT *)info;
		if (ct->ct_backchannelxprt == NULL) {
			xprt->xp_p2 = ct;
			ct->ct_backchannelxprt = xprt;
		}
		break;

	default:
		mtx_unlock(&ct->ct_lock);
		return (FALSE);
	}

	mtx_unlock(&ct->ct_lock);
	return (TRUE);
}