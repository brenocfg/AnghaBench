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
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,void*) ;
struct timeval {int dummy; } ;
struct rpc_callextra {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rpcproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int CLNT_CALL_MBUF (int /*<<< orphan*/ *,struct rpc_callextra*,int /*<<< orphan*/ ,struct mbuf*,struct mbuf**,struct timeval) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int RPC_CANTDECODERES ; 
 int RPC_CANTENCODEARGS ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrmbuf_create (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 

enum clnt_stat
clnt_call_private(
	CLIENT		*cl,		/* client handle */
	struct rpc_callextra *ext,	/* call metadata */
	rpcproc_t	proc,		/* procedure number */
	xdrproc_t	xargs,		/* xdr routine for args */
	void		*argsp,		/* pointer to args */
	xdrproc_t	xresults,	/* xdr routine for results */
	void		*resultsp,	/* pointer to results */
	struct timeval	utimeout)	/* seconds to wait before giving up */
{
	XDR xdrs;
	struct mbuf *mreq;
	struct mbuf *mrep;
	enum clnt_stat stat;

	mreq = m_getcl(M_WAITOK, MT_DATA, 0);

	xdrmbuf_create(&xdrs, mreq, XDR_ENCODE);
	if (!xargs(&xdrs, argsp)) {
		m_freem(mreq);
		return (RPC_CANTENCODEARGS);
	}
	XDR_DESTROY(&xdrs);

	stat = CLNT_CALL_MBUF(cl, ext, proc, mreq, &mrep, utimeout);
	m_freem(mreq);

	if (stat == RPC_SUCCESS) {
		xdrmbuf_create(&xdrs, mrep, XDR_DECODE);
		if (!xresults(&xdrs, resultsp)) {
			XDR_DESTROY(&xdrs);
			return (RPC_CANTDECODERES);
		}
		XDR_DESTROY(&xdrs);
	}

	return (stat);
}