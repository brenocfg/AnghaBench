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
struct dom_binding {struct dom_binding* dom_pnext; int /*<<< orphan*/  dom_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  _yp_unbind (struct dom_binding*) ; 
 struct dom_binding* _ypbindlist ; 
 int /*<<< orphan*/  free (struct dom_binding*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
yp_unbind_locked(char *dom)
{
	struct dom_binding *ypb, *ypbp;

	ypbp = NULL;
	for (ypb = _ypbindlist; ypb; ypb = ypb->dom_pnext) {
		if (strcmp(dom, ypb->dom_domain) == 0) {
			_yp_unbind(ypb);
			if (ypbp)
				ypbp->dom_pnext = ypb->dom_pnext;
			else
				_ypbindlist = ypb->dom_pnext;
			free(ypb);
			return;
		}
		ypbp = ypb;
	}
	return;
}