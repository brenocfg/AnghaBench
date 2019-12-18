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
struct ypresp_maplist {struct ypmaplist* maps; int /*<<< orphan*/  stat; } ;
struct ypmaplist {int dummy; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct dom_binding {int /*<<< orphan*/  dom_client; } ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_MAPLIST ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,struct ypresp_maplist*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xdr_domainname ; 
 scalar_t__ xdr_ypresp_maplist ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_maplist(char *indomain, struct ypmaplist **outmaplist)
{
	struct dom_binding *ysd;
	struct ypresp_maplist ypml;
	struct timeval tv;
	int r;

	/* Sanity check */

	if (indomain == NULL || !strlen(indomain))
		return (YPERR_BADARGS);

	YPLOCK();
again:
	if (_yp_dobind(indomain, &ysd) != 0) {
		YPUNLOCK();
		return (YPERR_DOMAIN);
	}

	tv.tv_sec = _yplib_timeout;
	tv.tv_usec = 0;

	bzero((char *)&ypml, sizeof ypml);

	r = clnt_call(ysd->dom_client, YPPROC_MAPLIST,
		(xdrproc_t)xdr_domainname, &indomain,
		(xdrproc_t)xdr_ypresp_maplist, &ypml,tv);
	if (r != RPC_SUCCESS) {
		clnt_perror(ysd->dom_client, "yp_maplist: clnt_call");
		_yp_unbind(ysd);
		goto again;
	}
	if (!(r = ypprot_err(ypml.stat))) {
		*outmaplist = ypml.maps;
	}

	/* NO: xdr_free((xdrproc_t)xdr_ypresp_maplist, &ypml);*/
	YPUNLOCK();
	return (r);
}