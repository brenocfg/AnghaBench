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
struct TYPE_4__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_3__ {int /*<<< orphan*/  where; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct accepted_reply {int ar_stat; TYPE_2__ ar_vers; TYPE_1__ ar_results; int /*<<< orphan*/  ar_verf; } ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  enum accept_stat { ____Placeholder_accept_stat } accept_stat ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GARBAGE_ARGS 133 
#define  PROC_UNAVAIL 132 
#define  PROG_MISMATCH 131 
#define  PROG_UNAVAIL 130 
#define  SUCCESS 129 
#define  SYSTEM_ERR 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque_auth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcvers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_accepted_reply(XDR *xdrs, struct accepted_reply *ar)
{
	enum accept_stat *par_stat;

	assert(xdrs != NULL);
	assert(ar != NULL);

	par_stat = &ar->ar_stat;

	/* personalized union, rather than calling xdr_union */
	if (! xdr_opaque_auth(xdrs, &(ar->ar_verf)))
		return (FALSE);
	if (! xdr_enum(xdrs, (enum_t *) par_stat))
		return (FALSE);
	switch (ar->ar_stat) {

	case SUCCESS:
		return ((*(ar->ar_results.proc))(xdrs, ar->ar_results.where));

	case PROG_MISMATCH:
		if (!xdr_rpcvers(xdrs, &(ar->ar_vers.low)))
			return (FALSE);
		return (xdr_rpcvers(xdrs, &(ar->ar_vers.high)));

	case GARBAGE_ARGS:
	case SYSTEM_ERR:
	case PROC_UNAVAIL:
	case PROG_UNAVAIL:
		break;
	}
	return (TRUE);  /* TRUE => open ended set of problems */
}