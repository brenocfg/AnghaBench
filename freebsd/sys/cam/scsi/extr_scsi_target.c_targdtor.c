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
typedef  union ccb {int dummy; } ccb ;
struct targ_softc {int /*<<< orphan*/ * path; int /*<<< orphan*/ * periph; int /*<<< orphan*/  abort_queue; int /*<<< orphan*/  user_ccb_queue; } ;
struct targ_cmd_descr {int dummy; } ;
typedef  struct targ_cmd_descr ccb_hdr ;
struct cam_periph {int /*<<< orphan*/ * softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TARG ; 
 struct targ_cmd_descr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct targ_cmd_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct targ_cmd_descr*,int /*<<< orphan*/ ) ; 
 TYPE_1__ periph_links ; 
 int /*<<< orphan*/  targfreeccb (struct targ_softc*,union ccb*) ; 
 int /*<<< orphan*/  tqe ; 

__attribute__((used)) static void
targdtor(struct cam_periph *periph)
{
	struct targ_softc     *softc;
	struct ccb_hdr	      *ccb_h;
	struct targ_cmd_descr *descr;

	softc = (struct targ_softc *)periph->softc;

	/* 
	 * targdisable() aborts CCBs back to the user and leaves them
	 * on user_ccb_queue and abort_queue in case the user is still
	 * interested in them.  We free them now.
	 */
	while ((ccb_h = TAILQ_FIRST(&softc->user_ccb_queue)) != NULL) {
		TAILQ_REMOVE(&softc->user_ccb_queue, ccb_h, periph_links.tqe);
		targfreeccb(softc, (union ccb *)ccb_h);
	}
	while ((descr = TAILQ_FIRST(&softc->abort_queue)) != NULL) {
		TAILQ_REMOVE(&softc->abort_queue, descr, tqe);
		free(descr, M_TARG);
	}

	softc->periph = NULL;
	softc->path = NULL;
	periph->softc = NULL;
}