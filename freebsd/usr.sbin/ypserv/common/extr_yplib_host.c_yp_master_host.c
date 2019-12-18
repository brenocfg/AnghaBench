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
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  YPPROC_MASTER ; 
 int /*<<< orphan*/  _yplib_host_timeout ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,struct ypresp_master*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct ypresp_master*,int /*<<< orphan*/ ,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_master ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_master_host(CLIENT *client, char *indomain, char *inmap, char **outname)
{
	struct ypresp_master yprm;
	struct ypreq_nokey yprnk;
	struct timeval tv;
	int r;

	tv.tv_sec = _yplib_host_timeout;
	tv.tv_usec = 0;
	yprnk.domain = indomain;
	yprnk.map = inmap;

	memset(&yprm, 0, sizeof yprm);

	r = clnt_call(client, YPPROC_MASTER,
	    (xdrproc_t)xdr_ypreq_nokey, &yprnk,
	    (xdrproc_t)xdr_ypresp_master, &yprm, tv);
	if (r != RPC_SUCCESS)
		clnt_perror(client, "yp_master: clnt_call");
	if (!(r = ypprot_err(yprm.stat)))
		*outname = strdup(yprm.peer);
	xdr_free((xdrproc_t)xdr_ypresp_master, (char *)&yprm);

	return (r);
}