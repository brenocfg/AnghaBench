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
struct ciss_softc {scalar_t__ ciss_perf; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  cr_qhead_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct ciss_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  ciss_complete (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_done (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_perf_done (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
ciss_cam_poll(struct cam_sim *sim)
{
    cr_qhead_t qh;
    struct ciss_softc	*sc = cam_sim_softc(sim);

    debug_called(2);

    STAILQ_INIT(&qh);
    if (sc->ciss_perf)
	ciss_perf_done(sc, &qh);
    else
	ciss_done(sc, &qh);
    ciss_complete(sc, &qh);
}