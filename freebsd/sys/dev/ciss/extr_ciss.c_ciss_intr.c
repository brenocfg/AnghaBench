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
struct ciss_softc {int /*<<< orphan*/  ciss_mtx; } ;
typedef  int /*<<< orphan*/  cr_qhead_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_complete (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_done (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ciss_intr(void *arg)
{
    cr_qhead_t qh;
    struct ciss_softc	*sc = (struct ciss_softc *)arg;

    /*
     * The only interrupt we recognise indicates that there are
     * entries in the outbound post queue.
     */
    STAILQ_INIT(&qh);
    ciss_done(sc, &qh);
    mtx_lock(&sc->ciss_mtx);
    ciss_complete(sc, &qh);
    mtx_unlock(&sc->ciss_mtx);
}