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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_int_disable (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_int_disable_sync(struct bxe_softc *sc,
                     int              disable_hw)
{
    if (disable_hw) {
        /* prevent the HW from sending interrupts */
        bxe_int_disable(sc);
    }

    /* XXX need a way to synchronize ALL irqs (intr_mtx?) */
    /* make sure all ISRs are done */

    /* XXX make sure sp_task is not running */
    /* cancel and flush work queues */
}