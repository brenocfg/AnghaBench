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
struct scb {int flags; struct ahc_softc* ahc_softc; } ;
struct ahc_softc {int /*<<< orphan*/  timedout_scbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct scb*,int /*<<< orphan*/ ) ; 
 int SCB_ACTIVE ; 
 int SCB_TIMEDOUT ; 
 int /*<<< orphan*/  ahc_wakeup_recovery_thread (struct ahc_softc*) ; 
 int /*<<< orphan*/  timedout_links ; 

void
ahc_timeout(struct scb *scb)
{
	struct ahc_softc *ahc;

	ahc = scb->ahc_softc;
	if ((scb->flags & SCB_ACTIVE) != 0) {
		if ((scb->flags & SCB_TIMEDOUT) == 0) {
			LIST_INSERT_HEAD(&ahc->timedout_scbs, scb,
					 timedout_links);
			scb->flags |= SCB_TIMEDOUT;
		}
		ahc_wakeup_recovery_thread(ahc);
	}
}