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
struct pps_softc {int /*<<< orphan*/  pps_state; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  pps_capture (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpiopps_ifltr(void *arg)
{
	struct pps_softc *sc = arg;

	/*
	 * There is no locking here by design... The kernel cleverly captures
	 * the current time into an area of the pps_state structure which is
	 * written only by the pps_capture() routine and read only by the
	 * pps_event() routine.  We don't need lock-based management of access
	 * to the capture area because we have time-based access management:  we
	 * can't be reading and writing concurently because we can't be running
	 * both the threaded and filter handlers concurrently (because a new
	 * hardware interrupt can't happen until the threaded handler for the
	 * current interrupt exits, after which the system does the EOI that
	 * enables a new hardware interrupt).
	 */
	pps_capture(&sc->pps_state);
	return (FILTER_SCHEDULE_THREAD);
}