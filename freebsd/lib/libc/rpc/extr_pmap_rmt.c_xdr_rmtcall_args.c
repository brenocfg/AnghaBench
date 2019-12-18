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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int ;
struct rmtcallargs {scalar_t__ arglen; int /*<<< orphan*/  args_ptr; int /*<<< orphan*/  (* xdr_args ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ proc; scalar_t__ vers; scalar_t__ prog; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_long (int /*<<< orphan*/ *,scalar_t__*) ; 

bool_t
xdr_rmtcall_args(XDR *xdrs, struct rmtcallargs *cap)
{
	u_int lenposition, argposition, position;

	assert(xdrs != NULL);
	assert(cap != NULL);

	if (xdr_u_long(xdrs, &(cap->prog)) &&
	    xdr_u_long(xdrs, &(cap->vers)) &&
	    xdr_u_long(xdrs, &(cap->proc))) {
		lenposition = XDR_GETPOS(xdrs);
		if (! xdr_u_long(xdrs, &(cap->arglen)))
		    return (FALSE);
		argposition = XDR_GETPOS(xdrs);
		if (! (*(cap->xdr_args))(xdrs, cap->args_ptr))
		    return (FALSE);
		position = XDR_GETPOS(xdrs);
		cap->arglen = (u_long)position - (u_long)argposition;
		XDR_SETPOS(xdrs, lenposition);
		if (! xdr_u_long(xdrs, &(cap->arglen)))
		    return (FALSE);
		XDR_SETPOS(xdrs, position);
		return (TRUE);
	}
	return (FALSE);
}