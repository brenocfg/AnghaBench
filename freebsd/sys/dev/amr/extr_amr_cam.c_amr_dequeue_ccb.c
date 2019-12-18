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
union ccb {int /*<<< orphan*/  ccb_h; } ;
struct amr_softc {int /*<<< orphan*/  amr_cam_ccbq; } ;
struct TYPE_2__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ sim_links ; 

__attribute__((used)) static __inline union ccb *
amr_dequeue_ccb(struct amr_softc *sc)
{
	union ccb	*ccb;

	if ((ccb = (union ccb *)TAILQ_FIRST(&sc->amr_cam_ccbq)) != NULL)
		TAILQ_REMOVE(&sc->amr_cam_ccbq, &ccb->ccb_h, sim_links.tqe);
	return(ccb);
}