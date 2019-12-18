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
struct bxe_softc {int num_queues; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_init_tx_ring_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
bxe_init_tx_rings(struct bxe_softc *sc)
{
    int i;

    for (i = 0; i < sc->num_queues; i++) {
        bxe_init_tx_ring_one(&sc->fp[i]);
    }
}