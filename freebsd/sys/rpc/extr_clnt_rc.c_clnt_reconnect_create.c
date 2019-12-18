#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_len; } ;
struct TYPE_8__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int tv_sec; int tv_usec; } ;
struct rc_data {size_t rc_sendsz; size_t rc_recvsz; char* rc_waitchan; int /*<<< orphan*/ * rc_client; int /*<<< orphan*/  rc_ucred; void* rc_closed; void* rc_connecting; scalar_t__ rc_intr; void* rc_privport; int /*<<< orphan*/  rc_retries; TYPE_2__ rc_retry; TYPE_1__ rc_timeout; int /*<<< orphan*/  rc_vers; int /*<<< orphan*/  rc_prog; struct netconfig* rc_nconf; int /*<<< orphan*/  rc_addr; int /*<<< orphan*/  rc_lock; } ;
struct netconfig {int dummy; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_11__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_10__ {int /*<<< orphan*/  cf_stat; } ;
struct TYPE_9__ {int cl_refs; int /*<<< orphan*/ * cl_netid; int /*<<< orphan*/ * cl_tp; int /*<<< orphan*/  cl_auth; scalar_t__ cl_private; int /*<<< orphan*/ * cl_ops; } ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RPC_UNKNOWNADDR ; 
 int /*<<< orphan*/  authnone_create () ; 
 int /*<<< orphan*/  clnt_reconnect_ops ; 
 int /*<<< orphan*/  crdup (int /*<<< orphan*/ ) ; 
 TYPE_5__* curthread ; 
 void* mem_alloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ rpc_createerr ; 

CLIENT *
clnt_reconnect_create(
	struct netconfig *nconf,	/* network type */
	struct sockaddr *svcaddr,	/* servers address */
	rpcprog_t program,		/* program number */
	rpcvers_t version,		/* version number */
	size_t sendsz,			/* buffer recv size */
	size_t recvsz)			/* buffer send size */
{
	CLIENT *cl = NULL;		/* client handle */
	struct rc_data *rc = NULL;	/* private data */

	if (svcaddr == NULL) {
		rpc_createerr.cf_stat = RPC_UNKNOWNADDR;
		return (NULL);
	}

	cl = mem_alloc(sizeof (CLIENT));
	rc = mem_alloc(sizeof (*rc));
	mtx_init(&rc->rc_lock, "rc->rc_lock", NULL, MTX_DEF);
	(void) memcpy(&rc->rc_addr, svcaddr, (size_t)svcaddr->sa_len);
	rc->rc_nconf = nconf;
	rc->rc_prog = program;
	rc->rc_vers = version;
	rc->rc_sendsz = sendsz;
	rc->rc_recvsz = recvsz;
	rc->rc_timeout.tv_sec = -1;
	rc->rc_timeout.tv_usec = -1;
	rc->rc_retry.tv_sec = 3;
	rc->rc_retry.tv_usec = 0;
	rc->rc_retries = INT_MAX;
	rc->rc_privport = FALSE;
	rc->rc_waitchan = "rpcrecv";
	rc->rc_intr = 0;
	rc->rc_connecting = FALSE;
	rc->rc_closed = FALSE;
	rc->rc_ucred = crdup(curthread->td_ucred);
	rc->rc_client = NULL;

	cl->cl_refs = 1;
	cl->cl_ops = &clnt_reconnect_ops;
	cl->cl_private = (caddr_t)(void *)rc;
	cl->cl_auth = authnone_create();
	cl->cl_tp = NULL;
	cl->cl_netid = NULL;
	return (cl);
}