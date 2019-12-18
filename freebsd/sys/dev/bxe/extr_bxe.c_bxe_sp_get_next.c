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
struct eth_spe {int dummy; } ;
struct bxe_softc {scalar_t__ spq_prod_idx; struct eth_spe* spq_prod_bd; struct eth_spe* spq; struct eth_spe* spq_last_bd; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct eth_spe *bxe_sp_get_next(struct bxe_softc *sc)
{
    struct eth_spe *next_spe = sc->spq_prod_bd;

    if (sc->spq_prod_bd == sc->spq_last_bd) {
        /* wrap back to the first eth_spq */
        sc->spq_prod_bd = sc->spq;
        sc->spq_prod_idx = 0;
    } else {
        sc->spq_prod_bd++;
        sc->spq_prod_idx++;
    }

    return (next_spe);
}