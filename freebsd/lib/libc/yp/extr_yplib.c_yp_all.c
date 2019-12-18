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
typedef  scalar_t__ u_long ;
struct ypreq_nokey {char* domain; char* map; } ;
struct ypall_callback {scalar_t__ data; int /*<<< orphan*/  foreach; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct dom_binding {struct sockaddr_in dom_server_addr; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int RPC_ANYSOCK ; 
 scalar_t__ RPC_SUCCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int YPERR_PMAP ; 
 int YPERR_RPC ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_ALL ; 
 int /*<<< orphan*/  YPPROG ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 int /*<<< orphan*/  YPVERS ; 
 scalar_t__ YP_NOMORE ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,scalar_t__*,struct timeval) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_all_seq ; 
 int ypprot_err (scalar_t__) ; 
 int /*<<< orphan*/  ypresp_allfn ; 
 void* ypresp_data ; 

int
yp_all(char *indomain, char *inmap, struct ypall_callback *incallback)
{
	struct ypreq_nokey yprnk;
	struct dom_binding *ysd;
	struct timeval tv;
	struct sockaddr_in clnt_sin;
	CLIENT *clnt;
	u_long status, savstat;
	int clnt_sock;
	int retries = 0;
	/* Sanity check */

	if (indomain == NULL || !strlen(indomain) ||
	    inmap == NULL || !strlen(inmap))
		return (YPERR_BADARGS);

	YPLOCK();
again:
	if (retries > MAX_RETRIES) {
		YPUNLOCK();
		return (YPERR_RPC);
	}

	if (_yp_dobind(indomain, &ysd) != 0) {
		YPUNLOCK();
		return (YPERR_DOMAIN);
	}

	tv.tv_sec = _yplib_timeout;
	tv.tv_usec = 0;

	/* YPPROC_ALL manufactures its own channel to ypserv using TCP */

	clnt_sock = RPC_ANYSOCK;
	clnt_sin = ysd->dom_server_addr;
	clnt_sin.sin_port = 0;
	clnt = clnttcp_create(&clnt_sin, YPPROG, YPVERS, &clnt_sock, 0, 0);
	if (clnt == NULL) {
		YPUNLOCK();
		printf("clnttcp_create failed\n");
		return (YPERR_PMAP);
	}

	yprnk.domain = indomain;
	yprnk.map = inmap;
	ypresp_allfn = incallback->foreach;
	ypresp_data = (void *)incallback->data;

	if (clnt_call(clnt, YPPROC_ALL,
		(xdrproc_t)xdr_ypreq_nokey, &yprnk,
		(xdrproc_t)xdr_ypresp_all_seq, &status, tv) != RPC_SUCCESS) {
			clnt_perror(clnt, "yp_all: clnt_call");
			clnt_destroy(clnt);
			_yp_unbind(ysd);
			retries++;
			goto again;
	}

	clnt_destroy(clnt);
	savstat = status;
	xdr_free((xdrproc_t)xdr_ypresp_all_seq, &status);	/* not really needed... */
	YPUNLOCK();
	if (savstat != YP_NOMORE)
		return (ypprot_err(savstat));
	return (0);
}