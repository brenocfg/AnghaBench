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
struct TYPE_2__ {int func_code; union ccb* targ_descr; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ctio_descr {union ccb* buf; } ;

/* Variables and functions */
#define  XPT_ACCEPT_TARGET_IO 130 
#define  XPT_CONT_TARGET_IO 129 
#define  XPT_IMMEDIATE_NOTIFY 128 
 int /*<<< orphan*/  free (union ccb*) ; 
 int /*<<< orphan*/  num_ctios ; 

void
free_ccb(union ccb *ccb)
{
	switch (ccb->ccb_h.func_code) {
	case XPT_CONT_TARGET_IO:
	{
		struct ctio_descr *c_descr;

		c_descr = (struct ctio_descr *)ccb->ccb_h.targ_descr;
		free(c_descr->buf);
		num_ctios--;
		/* FALLTHROUGH */
	}
	case XPT_ACCEPT_TARGET_IO:
		free(ccb->ccb_h.targ_descr);
		/* FALLTHROUGH */
	case XPT_IMMEDIATE_NOTIFY:
	default:
		free(ccb);
		break;
	}
}