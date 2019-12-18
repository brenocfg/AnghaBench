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
struct bxe_softc {int /*<<< orphan*/  sp_tq_task; int /*<<< orphan*/  sp_tq; int /*<<< orphan*/  igu_dsb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int,char*) ; 
 int DBG_INTR ; 
 int DBG_SP ; 
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  USTORM_ID ; 
 int /*<<< orphan*/  bxe_ack_sb (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_intr_sp(void *xsc)
{
    struct bxe_softc *sc = (struct bxe_softc *)xsc;

    BLOGD(sc, (DBG_INTR | DBG_SP), "---> SP INTR <---\n");

    /* acknowledge and disable further slowpath interrupts */
    bxe_ack_sb(sc, sc->igu_dsb_id, USTORM_ID, 0, IGU_INT_DISABLE, 0);

    /* schedule slowpath handler */
    taskqueue_enqueue(sc->sp_tq, &sc->sp_tq_task);
}