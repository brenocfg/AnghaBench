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
struct audata {int /*<<< orphan*/  au_mpos; int /*<<< orphan*/  au_marshed; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct audata* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_PUTBYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
authunix_marshal(AUTH *auth, XDR *xdrs)
{
	struct audata *au;

	assert(auth != NULL);
	assert(xdrs != NULL);

	au = AUTH_PRIVATE(auth);
	return (XDR_PUTBYTES(xdrs, au->au_marshed, au->au_mpos));
}