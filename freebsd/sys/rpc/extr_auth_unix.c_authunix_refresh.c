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
typedef  int /*<<< orphan*/  uint32_t ;
struct xucred {int dummy; } ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
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
 int /*<<< orphan*/  XDR_SETPOS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  marshal_new_auth (TYPE_3__*) ; 
 int xdr_authunix_parms (TYPE_2__*,int /*<<< orphan*/ *,struct xucred*) ; 
 int /*<<< orphan*/  xdrmem_create (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
authunix_refresh(AUTH *auth, void *dummy)
{
	struct audata *au = AUTH_PRIVATE(auth);
	struct xucred xcr;
	uint32_t time;
	struct timeval now;
	XDR xdrs;
	int stat;

	if (auth->ah_cred.oa_base == au->au_origcred.oa_base) {
		/* there is no hope.  Punt */
		return (FALSE);
	}
	au->au_shfaults ++;

	/* first deserialize the creds back into a struct ucred */
	xdrmem_create(&xdrs, au->au_origcred.oa_base,
	    au->au_origcred.oa_length, XDR_DECODE);
	stat = xdr_authunix_parms(&xdrs, &time, &xcr);
	if (! stat)
		goto done;

	/* update the time and serialize in place */
	getmicrotime(&now);
	time = now.tv_sec;
	xdrs.x_op = XDR_ENCODE;
	XDR_SETPOS(&xdrs, 0);

	stat = xdr_authunix_parms(&xdrs, &time, &xcr);
	if (! stat)
		goto done;
	auth->ah_cred = au->au_origcred;
	marshal_new_auth(auth);
done:
	XDR_DESTROY(&xdrs);
	return (stat);
}