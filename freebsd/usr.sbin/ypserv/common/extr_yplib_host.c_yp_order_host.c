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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ypresp_order {int /*<<< orphan*/  stat; int /*<<< orphan*/  ordernum; } ;
struct ypreq_nokey {char* domain; char* map; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  YPPROC_ORDER ; 
 int /*<<< orphan*/  _yplib_host_timeout ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,struct ypresp_order*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct ypresp_order*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_order ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_order_host(CLIENT *client, char *indomain, char *inmap, u_int32_t *outorder)
{
	struct ypresp_order ypro;
	struct ypreq_nokey yprnk;
	struct timeval tv;
	int r;

	tv.tv_sec = _yplib_host_timeout;
	tv.tv_usec = 0;

	yprnk.domain = indomain;
	yprnk.map = inmap;

	memset(&ypro, 0, sizeof ypro);

	r = clnt_call(client, YPPROC_ORDER,
	    (xdrproc_t)xdr_ypreq_nokey, &yprnk,
	    (xdrproc_t)xdr_ypresp_order, &ypro, tv);
	if (r != RPC_SUCCESS)
		clnt_perror(client, "yp_order_host: clnt_call");
	*outorder = ypro.ordernum;
	xdr_free((xdrproc_t)xdr_ypresp_order, (char *)&ypro);

	return ypprot_err(ypro.stat);
}