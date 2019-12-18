#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_6__ {int valdat_len; int /*<<< orphan*/  valdat_val; } ;
struct ypresp_val {TYPE_2__ val; int /*<<< orphan*/  stat; } ;
struct TYPE_5__ {char* keydat_val; int keydat_len; } ;
struct ypreq_key {char* domain; char* map; TYPE_1__ key; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct dom_binding {int /*<<< orphan*/  dom_client; } ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int RPC_SUCCESS ; 
 scalar_t__ TRUE ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int YPERR_RESRC ; 
 int YPERR_RPC ; 
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPPROC_MATCH ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 scalar_t__ _yp_dobind (char*,struct dom_binding**) ; 
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 int /*<<< orphan*/  _yplib_timeout ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_key*,int /*<<< orphan*/ ,struct ypresp_val*,struct timeval) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct ypresp_val*) ; 
 scalar_t__ xdr_ypreq_key ; 
 scalar_t__ xdr_ypresp_val ; 
 int /*<<< orphan*/  ypmatch_cache_insert (struct dom_binding*,char*,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ ypmatch_cache_lookup (struct dom_binding*,char*,TYPE_1__*,TYPE_2__*) ; 
 int ypprot_err (int /*<<< orphan*/ ) ; 

int
yp_match(char *indomain, char *inmap, const char *inkey, int inkeylen,
    char **outval, int *outvallen)
{
	struct dom_binding *ysd;
	struct ypresp_val yprv;
	struct timeval tv;
	struct ypreq_key yprk;
	int r;
	int retries = 0;
	*outval = NULL;
	*outvallen = 0;

	/* Sanity check */

	if (inkey == NULL || !strlen(inkey) || inkeylen <= 0 ||
	    inmap == NULL || !strlen(inmap) ||
	    indomain == NULL || !strlen(indomain))
		return (YPERR_BADARGS);

	YPLOCK();
	if (_yp_dobind(indomain, &ysd) != 0) {
		YPUNLOCK();
		return(YPERR_DOMAIN);
	}

	yprk.domain = indomain;
	yprk.map = inmap;
	yprk.key.keydat_val = (char *)inkey;
	yprk.key.keydat_len = inkeylen;

#ifdef YPMATCHCACHE
	if (ypmatch_cache_lookup(ysd, yprk.map, &yprk.key, &yprv.val) == TRUE) {
/*
	if (!strcmp(_yp_domain, indomain) && ypmatch_find(inmap, inkey,
	    inkeylen, &yprv.val.valdat_val, &yprv.val.valdat_len)) {
*/
		*outvallen = yprv.val.valdat_len;
		*outval = (char *)malloc(*outvallen+1);
		if (*outval == NULL) {
			_yp_unbind(ysd);
			*outvallen = 0;
			YPUNLOCK();
			return (YPERR_RESRC);
		}
		bcopy(yprv.val.valdat_val, *outval, *outvallen);
		(*outval)[*outvallen] = '\0';
		YPUNLOCK();
		return (0);
	}
	_yp_unbind(ysd);
#endif

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

	bzero((char *)&yprv, sizeof yprv);

	r = clnt_call(ysd->dom_client, YPPROC_MATCH,
		(xdrproc_t)xdr_ypreq_key, &yprk,
		(xdrproc_t)xdr_ypresp_val, &yprv, tv);
	if (r != RPC_SUCCESS) {
		clnt_perror(ysd->dom_client, "yp_match: clnt_call");
		_yp_unbind(ysd);
		retries++;
		goto again;
	}

	if (!(r = ypprot_err(yprv.stat))) {
		*outvallen = yprv.val.valdat_len;
		*outval = (char *)malloc(*outvallen+1);
		if (*outval == NULL) {
			_yp_unbind(ysd);
			*outvallen = 0;
			xdr_free((xdrproc_t)xdr_ypresp_val, &yprv);
			YPUNLOCK();
			return (YPERR_RESRC);
		}
		bcopy(yprv.val.valdat_val, *outval, *outvallen);
		(*outval)[*outvallen] = '\0';
#ifdef YPMATCHCACHE
		ypmatch_cache_insert(ysd, yprk.map, &yprk.key, &yprv.val);
#endif
	}

	xdr_free((xdrproc_t)xdr_ypresp_val, &yprv);
	YPUNLOCK();
	return (r);
}