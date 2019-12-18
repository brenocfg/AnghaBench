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
struct targ_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 int /*<<< orphan*/  CAM_DEBUG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_TARG ; 
#define  XPT_ACCEPT_TARGET_IO 130 
 int /*<<< orphan*/  XPT_FC_IS_QUEUED (union ccb*) ; 
#define  XPT_IMMEDIATE_NOTIFY 129 
#define  XPT_IMMED_NOTIFY 128 
 int /*<<< orphan*/  free (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static void
targfreeccb(struct targ_softc *softc, union ccb *ccb)
{
	CAM_DEBUG_PRINT(CAM_DEBUG_PERIPH, ("targfreeccb descr %p and\n",
			ccb->ccb_h.targ_descr));
	free(ccb->ccb_h.targ_descr, M_TARG);

	switch (ccb->ccb_h.func_code) {
	case XPT_ACCEPT_TARGET_IO:
	case XPT_IMMED_NOTIFY:
	case XPT_IMMEDIATE_NOTIFY:
		CAM_DEBUG_PRINT(CAM_DEBUG_PERIPH, ("freeing ccb %p\n", ccb));
		free(ccb, M_TARG);
		break;
	default:
		/* Send back CCB if we got it from the periph */
		if (XPT_FC_IS_QUEUED(ccb)) {
			CAM_DEBUG_PRINT(CAM_DEBUG_PERIPH,
					("returning queued ccb %p\n", ccb));
			xpt_release_ccb(ccb);
		} else {
			CAM_DEBUG_PRINT(CAM_DEBUG_PERIPH,
					("freeing ccb %p\n", ccb));
			free(ccb, M_TARG);
		}
		break;
	}
}