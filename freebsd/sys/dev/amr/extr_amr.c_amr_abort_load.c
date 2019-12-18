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
struct amr_softc {int /*<<< orphan*/  amr_list_lock; } ;
struct amr_command {int /*<<< orphan*/  ac_status; struct amr_softc* ac_sc; } ;
typedef  int /*<<< orphan*/  ac_qhead_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_STATUS_ABORTED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  amr_complete (struct amr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amr_enqueue_completed (struct amr_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amr_init_qhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
amr_abort_load(struct amr_command *ac)
{
    ac_qhead_t head;
    struct amr_softc *sc = ac->ac_sc;

    mtx_assert(&sc->amr_list_lock, MA_OWNED);

    ac->ac_status = AMR_STATUS_ABORTED;
    amr_init_qhead(&head);
    amr_enqueue_completed(ac, &head);

    mtx_unlock(&sc->amr_list_lock);
    amr_complete(sc, &head);
    mtx_lock(&sc->amr_list_lock);
}