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
struct uni_ierr {scalar_t__ ie; } ;
struct TYPE_2__ {int errcnt; struct uni_ierr* err; } ;
struct uni {TYPE_1__ cx; } ;

/* Variables and functions */
 scalar_t__ UNI_IE_CAUSE ; 

void
uni_vfy_remove_cause(struct uni *uni)
{
	struct uni_ierr *e1, *e0;

	e0 = e1 = uni->cx.err;
	while (e1 < uni->cx.err + uni->cx.errcnt) {
		if (e1->ie != UNI_IE_CAUSE) {
			if (e0 != e1)
				*e0 = *e1;
			e0++;
		}
		e1++;
	}
	uni->cx.errcnt = e0 - uni->cx.err;
}