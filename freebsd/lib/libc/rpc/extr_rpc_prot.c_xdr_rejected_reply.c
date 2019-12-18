#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct rejected_reply {int rj_stat; int rj_why; TYPE_1__ rj_vers; } ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  enum reject_stat { ____Placeholder_reject_stat } reject_stat ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
#define  AUTH_ERROR 129 
 int /*<<< orphan*/  FALSE ; 
#define  RPC_MISMATCH 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcvers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t 
xdr_rejected_reply(XDR *xdrs, struct rejected_reply *rr)
{
	enum reject_stat *prj_stat;
	enum auth_stat *prj_why;

	assert(xdrs != NULL);
	assert(rr != NULL);

	prj_stat = &rr->rj_stat;

	/* personalized union, rather than calling xdr_union */
	if (! xdr_enum(xdrs, (enum_t *) prj_stat))
		return (FALSE);
	switch (rr->rj_stat) {

	case RPC_MISMATCH:
		if (! xdr_rpcvers(xdrs, &(rr->rj_vers.low)))
			return (FALSE);
		return (xdr_rpcvers(xdrs, &(rr->rj_vers.high)));

	case AUTH_ERROR:
		prj_why = &rr->rj_why;
		return (xdr_enum(xdrs, (enum_t *) prj_why));
	}
	/* NOTREACHED */
	assert(0);
	return (FALSE);
}