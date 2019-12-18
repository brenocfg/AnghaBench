#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct sockaddr {scalar_t__ sa_family; } ;
struct netconfig {long nc_semantics; int /*<<< orphan*/  nc_device; int /*<<< orphan*/  nc_netid; int /*<<< orphan*/  nc_protofmly; } ;
struct netbuf {scalar_t__ buf; } ;
struct __rpc_sockinfo {scalar_t__ si_af; int /*<<< orphan*/  si_socktype; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  one ;
typedef  scalar_t__ bool_t ;
struct TYPE_8__ {int /*<<< orphan*/  re_errno; } ;
struct TYPE_10__ {TYPE_1__ cf_error; void* cf_stat; } ;
struct TYPE_9__ {char* cl_netid; char* cl_tp; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_CONTROL (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSET_FD_CLOSE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
#define  NC_TPI_CLTS 130 
#define  NC_TPI_COTS 129 
#define  NC_TPI_COTS_ORD 128 
 int RPC_ANYFD ; 
 void* RPC_SYSTEMERROR ; 
 void* RPC_UNKNOWNHOST ; 
 void* RPC_UNKNOWNPROTO ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  __rpc_fd2sockinfo (int,struct __rpc_sockinfo*) ; 
 int __rpc_nconf2fd (struct netconfig const*) ; 
 int __rpc_raise_fd (int) ; 
 long __rpc_socktype2seman (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  _setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bindresvport (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* clnt_dg_create (int,struct netbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* clnt_vc_create (int,struct netbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__ rpc_createerr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

CLIENT *
clnt_tli_create(int fd, const struct netconfig *nconf,
	struct netbuf *svcaddr, rpcprog_t prog, rpcvers_t vers,
	uint sendsz, uint recvsz)
{
	CLIENT *cl;			/* client handle */
	bool_t madefd = FALSE;		/* whether fd opened here */
	long servtype;
	int one = 1;
	struct __rpc_sockinfo si;
	extern int __rpc_minfd;

	if (fd == RPC_ANYFD) {
		if (nconf == NULL) {
			rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
			return (NULL);
		}

		fd = __rpc_nconf2fd(nconf);

		if (fd == -1)
			goto err;
		if (fd < __rpc_minfd)
			fd = __rpc_raise_fd(fd);
		madefd = TRUE;
		servtype = nconf->nc_semantics;
		if (!__rpc_fd2sockinfo(fd, &si))
			goto err;
		bindresvport(fd, NULL);
	} else {
		if (!__rpc_fd2sockinfo(fd, &si))
			goto err;
		servtype = __rpc_socktype2seman(si.si_socktype);
		if (servtype == -1) {
			rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
			return (NULL);
		}
	}

	if (si.si_af != ((struct sockaddr *)svcaddr->buf)->sa_family) {
		rpc_createerr.cf_stat = RPC_UNKNOWNHOST;	/* XXX */
		goto err1;
	}

	switch (servtype) {
	case NC_TPI_COTS:
		cl = clnt_vc_create(fd, svcaddr, prog, vers, sendsz, recvsz);
		break;
	case NC_TPI_COTS_ORD:
		if (nconf && ((strcmp(nconf->nc_protofmly, "inet") == 0))) {
			_setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one,
			    sizeof (one));
		}
		cl = clnt_vc_create(fd, svcaddr, prog, vers, sendsz, recvsz);
		break;
	case NC_TPI_CLTS:
		cl = clnt_dg_create(fd, svcaddr, prog, vers, sendsz, recvsz);
		break;
	default:
		goto err;
	}

	if (cl == NULL)
		goto err1; /* borrow errors from clnt_dg/vc creates */
	if (nconf) {
		cl->cl_netid = strdup(nconf->nc_netid);
		cl->cl_tp = strdup(nconf->nc_device);
	} else {
		cl->cl_netid = "";
		cl->cl_tp = "";
	}
	if (madefd) {
		(void) CLNT_CONTROL(cl, CLSET_FD_CLOSE, NULL);
/*		(void) CLNT_CONTROL(cl, CLSET_POP_TIMOD, NULL);  */
	}

	return (cl);

err:
	rpc_createerr.cf_stat = RPC_SYSTEMERROR;
	rpc_createerr.cf_error.re_errno = errno;
err1:	if (madefd)
		(void)_close(fd);
	return (NULL);
}