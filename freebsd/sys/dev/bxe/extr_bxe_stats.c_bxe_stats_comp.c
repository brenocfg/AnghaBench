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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int /*<<< orphan*/  sp_err_timeout_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_ERR_STATS_TO ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DMAE_COMP_VAL ; 
 int hz ; 
 scalar_t__* stats_comp ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
bxe_stats_comp(struct bxe_softc *sc)
{
    uint32_t *stats_comp = BXE_SP(sc, stats_comp);
    int cnt = 10;

    while (*stats_comp != DMAE_COMP_VAL) {
        if (!cnt) {
            BLOGE(sc, "Timeout waiting for stats finished\n");
	    BXE_SET_ERROR_BIT(sc, BXE_ERR_STATS_TO);
            taskqueue_enqueue_timeout(taskqueue_thread,
                &sc->sp_err_timeout_task, hz/10);
            break;

        }

        cnt--;
        DELAY(1000);
    }

    return (1);
}