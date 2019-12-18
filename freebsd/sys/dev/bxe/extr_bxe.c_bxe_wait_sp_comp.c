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
typedef  int /*<<< orphan*/  uint8_t ;
struct bxe_softc {int /*<<< orphan*/  sp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned long atomic_load_acq_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline uint8_t
bxe_wait_sp_comp(struct bxe_softc *sc,
                 unsigned long    mask)
{
    unsigned long tmp;
    int tout = 5000; /* wait for 5 secs tops */

    while (tout--) {
        mb();
        if (!(atomic_load_acq_long(&sc->sp_state) & mask)) {
            return (TRUE);
        }

        DELAY(1000);
    }

    mb();

    tmp = atomic_load_acq_long(&sc->sp_state);
    if (tmp & mask) {
        BLOGE(sc, "Filtering completion timed out: "
                  "sp_state 0x%lx, mask 0x%lx\n",
              tmp, mask);
        return (FALSE);
    }

    return (FALSE);
}