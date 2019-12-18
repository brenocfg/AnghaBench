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
struct netbuf {struct netbuf* buf; } ;
struct t_bind {int qlen; struct netbuf addr; } ;
struct netconfig {char* nc_netid; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  M_RPC ; 
 int /*<<< orphan*/  SVC_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct netbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  rpcb_unset (scalar_t__,scalar_t__,struct netconfig*) ; 
 scalar_t__ svc_reg (int /*<<< orphan*/ *,scalar_t__,scalar_t__,void (*) (struct svc_req*,int /*<<< orphan*/ *),struct netconfig const*) ; 
 int /*<<< orphan*/ * svc_tli_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netconfig const*,struct t_bind*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netbuf* uaddr2taddr (struct netconfig const*,char const*) ; 
 int /*<<< orphan*/  xprt_unregister (int /*<<< orphan*/ *) ; 

SVCXPRT *
svc_tp_create(
	SVCPOOL *pool,
	void (*dispatch)(struct svc_req *, SVCXPRT *),
	rpcprog_t prognum,		/* Program number */
	rpcvers_t versnum,		/* Version number */
	const char *uaddr,		/* Address (or null for default) */
	const struct netconfig *nconf) /* Netconfig structure for the network */
{
	struct netconfig nconfcopy;
	struct netbuf *taddr;
	struct t_bind bind;
	SVCXPRT *xprt;

	if (nconf == NULL) {
		printf(
	"svc_tp_create: invalid netconfig structure for prog %u vers %u\n",
				(unsigned)prognum, (unsigned)versnum);
		return (NULL);
	}
	if (uaddr) {
		taddr = uaddr2taddr(nconf, uaddr);
		bind.addr = *taddr;
		free(taddr, M_RPC);
		bind.qlen = -1;
		xprt = svc_tli_create(pool, NULL, nconf, &bind, 0, 0);
		free(bind.addr.buf, M_RPC);
	} else {
		xprt = svc_tli_create(pool, NULL, nconf, NULL, 0, 0);
	}
	if (xprt == NULL) {
		return (NULL);
	}
	/*LINTED const castaway*/
	nconfcopy = *nconf;
	(void) rpcb_unset(prognum, versnum, &nconfcopy);
	if (svc_reg(xprt, prognum, versnum, dispatch, nconf) == FALSE) {
		printf(
		"svc_tp_create: Could not register prog %u vers %u on %s\n",
				(unsigned)prognum, (unsigned)versnum,
				nconf->nc_netid);
		xprt_unregister(xprt);
		SVC_RELEASE(xprt);
		return (NULL);
	}
	return (xprt);
}