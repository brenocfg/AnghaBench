#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_6__ {int valdat_len; int /*<<< orphan*/  valdat_val; } ;
struct TYPE_5__ {int keydat_len; int /*<<< orphan*/  keydat_val; } ;
struct ypresp_key_val {TYPE_3__ val; TYPE_2__ key; int /*<<< orphan*/  stat; } ;
struct TYPE_4__ {char* keydat_val; int keydat_len; } ;
struct ypreq_key {char* domain; char* map; TYPE_1__ key; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct dom_binding {int /*<<< orphan*/  dom_client; } ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int RPC_SUCCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int YPERR_RESRC ; 
 int YPERR_RPC ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_NEXT ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_key*,int /*<<< orphan*/ ,struct ypresp_key_val*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct ypresp_key_val*) ; 
 scalar_t__ xdr_ypreq_key ; 
 scalar_t__ xdr_ypresp_key_val ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_next(char *indomain, char *inmap, char *inkey, int inkeylen,
    char **outkey, int *outkeylen, char **outval, int *outvallen)
{
	struct ypresp_key_val yprkv;
	struct ypreq_key yprk;
	struct dom_binding *ysd;
	struct timeval tv;
	int r;
	int retries = 0;
	/* Sanity check */

	if (inkey == NULL || !strlen(inkey) || inkeylen <= 0 ||
	    inmap == NULL || !strlen(inmap) ||
	    indomain == NULL || !strlen(indomain))
		return (YPERR_BADARGS);

	*outkey = *outval = NULL;
	*outkeylen = *outvallen = 0;

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

	yprk.domain = indomain;
	yprk.map = inmap;
	yprk.key.keydat_val = inkey;
	yprk.key.keydat_len = inkeylen;
	bzero((char *)&yprkv, sizeof yprkv);

	r = clnt_call(ysd->dom_client, YPPROC_NEXT,
		(xdrproc_t)xdr_ypreq_key, &yprk,
		(xdrproc_t)xdr_ypresp_key_val, &yprkv, tv);
	if (r != RPC_SUCCESS) {
		clnt_perror(ysd->dom_client, "yp_next: clnt_call");
		_yp_unbind(ysd);
		retries++;
		goto again;
	}
	if (!(r = ypprot_err(yprkv.stat))) {
		*outkeylen = yprkv.key.keydat_len;
		*outkey = (char *)malloc(*outkeylen+1);
		if (*outkey == NULL) {
			_yp_unbind(ysd);
			*outkeylen = 0;
			xdr_free((xdrproc_t)xdr_ypresp_key_val, &yprkv);
			YPUNLOCK();
			return (YPERR_RESRC);
		}
		bcopy(yprkv.key.keydat_val, *outkey, *outkeylen);
		(*outkey)[*outkeylen] = '\0';
		*outvallen = yprkv.val.valdat_len;
		*outval = (char *)malloc(*outvallen+1);
		if (*outval == NULL) {
			free(*outkey);
			_yp_unbind(ysd);
			*outkeylen = *outvallen = 0;
			xdr_free((xdrproc_t)xdr_ypresp_key_val, &yprkv);
			YPUNLOCK();
			return (YPERR_RESRC);
		}
		bcopy(yprkv.val.valdat_val, *outval, *outvallen);
		(*outval)[*outvallen] = '\0';
	}

	xdr_free((xdrproc_t)xdr_ypresp_key_val, &yprkv);
	YPUNLOCK();
	return (r);
}