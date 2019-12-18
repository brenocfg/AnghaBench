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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct audata {int /*<<< orphan*/  au_mpos; int /*<<< orphan*/  au_marshed; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct audata* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_PUTBYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrmbuf_append (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static bool_t
authunix_marshal(AUTH *auth, uint32_t xid, XDR *xdrs, struct mbuf *args)
{
	struct audata *au;

	au = AUTH_PRIVATE(auth);
	if (!XDR_PUTBYTES(xdrs, au->au_marshed, au->au_mpos))
		return (FALSE);

	xdrmbuf_append(xdrs, args);

	return (TRUE);
}