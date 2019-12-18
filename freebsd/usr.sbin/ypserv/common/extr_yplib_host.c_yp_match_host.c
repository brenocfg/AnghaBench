#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_4__ {int valdat_len; int /*<<< orphan*/  valdat_val; } ;
struct ypresp_val {TYPE_2__ val; int /*<<< orphan*/  stat; } ;
struct TYPE_3__ {char* keydat_val; int keydat_len; } ;
struct ypreq_key {char* domain; char* map; TYPE_1__ key; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  YPPROC_MATCH ; 
 int /*<<< orphan*/  _yplib_host_timeout ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_key*,int /*<<< orphan*/ ,struct ypresp_val*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ypresp_val*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_ypreq_key ; 
 scalar_t__ xdr_ypresp_val ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_match_host(CLIENT *client, char *indomain, char *inmap, const char *inkey,
    int inkeylen, char **outval, int *outvallen)
{
	struct ypresp_val yprv;
	struct ypreq_key yprk;
	struct timeval tv;
	int r;

	*outval = NULL;
	*outvallen = 0;

	tv.tv_sec = _yplib_host_timeout;
	tv.tv_usec = 0;

	yprk.domain = indomain;
	yprk.map = inmap;
	yprk.key.keydat_val = (char *)inkey;
	yprk.key.keydat_len = inkeylen;

	memset(&yprv, 0, sizeof yprv);

	r = clnt_call(client, YPPROC_MATCH,
	    (xdrproc_t)xdr_ypreq_key, &yprk,
	    (xdrproc_t)xdr_ypresp_val, &yprv, tv);
	if (r != RPC_SUCCESS)
		clnt_perror(client, "yp_match_host: clnt_call");
	if ( !(r = ypprot_err(yprv.stat)) ) {
		*outvallen = yprv.val.valdat_len;
		*outval = malloc(*outvallen + 1);
		memcpy(*outval, yprv.val.valdat_val, *outvallen);
		(*outval)[*outvallen] = '\0';
	}
	xdr_free((xdrproc_t)xdr_ypresp_val, (char *)&yprv);

	return (r);
}