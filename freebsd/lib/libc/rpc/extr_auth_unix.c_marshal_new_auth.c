#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct audata {int /*<<< orphan*/  au_mpos; int /*<<< orphan*/  au_marshed; } ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_4__ {int /*<<< orphan*/  ah_verf; int /*<<< orphan*/  ah_cred; } ;
typedef  TYPE_1__ AUTH ;

/* Variables and functions */
 struct audata* AUTH_PRIVATE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX_AUTH_BYTES ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xdr_opaque_auth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
marshal_new_auth(AUTH *auth)
{
	XDR	xdr_stream;
	XDR	*xdrs = &xdr_stream;
	struct audata *au;

	assert(auth != NULL);

	au = AUTH_PRIVATE(auth);
	xdrmem_create(xdrs, au->au_marshed, MAX_AUTH_BYTES, XDR_ENCODE);
	if ((! xdr_opaque_auth(xdrs, &(auth->ah_cred))) ||
	    (! xdr_opaque_auth(xdrs, &(auth->ah_verf))))
		warnx("auth_none.c - Fatal marshalling problem");
	else
		au->au_mpos = XDR_GETPOS(xdrs);
	XDR_DESTROY(xdrs);
}