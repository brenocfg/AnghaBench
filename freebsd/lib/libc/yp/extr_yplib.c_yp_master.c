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
struct ypresp_master {int /*<<< orphan*/  peer; int /*<<< orphan*/  stat; } ;
struct ypreq_nokey {char* domain; char* map; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct dom_binding {int /*<<< orphan*/  dom_client; } ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_MASTER ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,struct ypresp_master*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct ypresp_master*) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_master ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_master(char *indomain, char *inmap, char **outname)
{
	struct dom_binding *ysd;
	struct ypresp_master yprm;
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

	bzero((char *)&yprm, sizeof yprm);

	r = clnt_call(ysd->dom_client, YPPROC_MASTER,
		(xdrproc_t)xdr_ypreq_nokey, &yprnk,
		(xdrproc_t)xdr_ypresp_master, &yprm, tv);
	if (r != RPC_SUCCESS) {
		clnt_perror(ysd->dom_client, "yp_master: clnt_call");
		_yp_unbind(ysd);
		goto again;
	}

	if (!(r = ypprot_err(yprm.stat))) {
		*outname = (char *)strdup(yprm.peer);
	}

	xdr_free((xdrproc_t)xdr_ypresp_master, &yprm);
	YPUNLOCK();
	return (r);
}