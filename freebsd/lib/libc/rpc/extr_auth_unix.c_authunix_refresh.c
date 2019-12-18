#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct authunix_parms {int /*<<< orphan*/  aup_time; int /*<<< orphan*/ * aup_gids; int /*<<< orphan*/ * aup_machname; } ;
struct TYPE_11__ {scalar_t__ oa_base; int /*<<< orphan*/  oa_length; } ;
struct audata {TYPE_1__ au_origcred; int /*<<< orphan*/  au_shfaults; } ;
typedef  int bool_t ;
struct TYPE_12__ {int /*<<< orphan*/  x_op; } ;
typedef  TYPE_2__ XDR ;
struct TYPE_13__ {TYPE_1__ ah_cred; } ;
typedef  TYPE_3__ AUTH ;

/* Variables and functions */
 struct audata* AUTH_PRIVATE (TYPE_3__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (TYPE_2__*) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  XDR_SETPOS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marshal_new_auth (TYPE_3__*) ; 
 int xdr_authunix_parms (TYPE_2__*,struct authunix_parms*) ; 
 int /*<<< orphan*/  xdrmem_create (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
authunix_refresh(AUTH *auth, void *dummy)
{
	struct audata *au = AUTH_PRIVATE(auth);
	struct authunix_parms aup;
	struct timeval now;
	XDR xdrs;
	int stat;

	assert(auth != NULL);

	if (auth->ah_cred.oa_base == au->au_origcred.oa_base) {
		/* there is no hope.  Punt */
		return (FALSE);
	}
	au->au_shfaults ++;

	/* first deserialize the creds back into a struct authunix_parms */
	aup.aup_machname = NULL;
	aup.aup_gids = NULL;
	xdrmem_create(&xdrs, au->au_origcred.oa_base,
	    au->au_origcred.oa_length, XDR_DECODE);
	stat = xdr_authunix_parms(&xdrs, &aup);
	if (! stat)
		goto done;

	/* update the time and serialize in place */
	(void)gettimeofday(&now, NULL);
	aup.aup_time = now.tv_sec;
	xdrs.x_op = XDR_ENCODE;
	XDR_SETPOS(&xdrs, 0);
	stat = xdr_authunix_parms(&xdrs, &aup);
	if (! stat)
		goto done;
	auth->ah_cred = au->au_origcred;
	marshal_new_auth(auth);
done:
	/* free the struct authunix_parms created by deserializing */
	xdrs.x_op = XDR_FREE;
	(void)xdr_authunix_parms(&xdrs, &aup);
	XDR_DESTROY(&xdrs);
	return (stat);
}