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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct ypresp_order {int ordernum; int /*<<< orphan*/  stat; } ;
struct ypreq_nokey {char* domain; char* map; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct dom_binding {int /*<<< orphan*/  dom_client; } ;

/* Variables and functions */
 int RPC_PROCUNAVAIL ; 
 int RPC_SUCCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int YPERR_YPERR ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_ORDER ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,struct ypresp_order*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct ypresp_order*) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_order ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_order(char *indomain, char *inmap, int *outorder)
{
 	struct dom_binding *ysd;
	struct ypresp_order ypro;
	struct ypreq_nokey yprnk;
	struct timeval tv;
	int r;

	/* Sanity check */

	if (indomain == NULL || !strlen(indomain) ||
	    inmap == NULL || !strlen(inmap))
		return (YPERR_BADARGS);

	YPLOCK();
again:
	if (_yp_dobind(indomain, &ysd) != 0) {
		YPUNLOCK();
		return (YPERR_DOMAIN);
	}

	tv.tv_sec = _yplib_timeout;
	tv.tv_usec = 0;

	yprnk.domain = indomain;
	yprnk.map = inmap;

	bzero((char *)(char *)&ypro, sizeof ypro);

	r = clnt_call(ysd->dom_client, YPPROC_ORDER,
		(xdrproc_t)xdr_ypreq_nokey, &yprnk,
		(xdrproc_t)xdr_ypresp_order, &ypro, tv);

	/*
	 * NIS+ in YP compat mode doesn't support the YPPROC_ORDER
	 * procedure.
	 */
	if (r == RPC_PROCUNAVAIL) {
		YPUNLOCK();
		return(YPERR_YPERR);
	}

	if (r != RPC_SUCCESS) {
		clnt_perror(ysd->dom_client, "yp_order: clnt_call");
		_yp_unbind(ysd);
		goto again;
	}

	if (!(r = ypprot_err(ypro.stat))) {
		*outorder = ypro.ordernum;
	}

	xdr_free((xdrproc_t)xdr_ypresp_order, &ypro);
	YPUNLOCK();
	return (r);
}