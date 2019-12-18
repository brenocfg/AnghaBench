#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {scalar_t__ spq_prod_bd; scalar_t__ spq_last_bd; scalar_t__ spq; TYPE_2__* def_sb; int /*<<< orphan*/ * dsb_sp_prod; scalar_t__ spq_prod_idx; int /*<<< orphan*/  cq_spq_left; } ;
struct TYPE_3__ {int /*<<< orphan*/ * index_values; } ;
struct TYPE_4__ {TYPE_1__ sp_sb; } ;

/* Variables and functions */
 size_t HC_SP_INDEX_ETH_DEF_CONS ; 
 int /*<<< orphan*/  MAX_SPQ_PENDING ; 
 scalar_t__ MAX_SP_DESC_CNT ; 
 int /*<<< orphan*/  atomic_store_rel_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_init_sp_ring(struct bxe_softc *sc)
{
    atomic_store_rel_long(&sc->cq_spq_left, MAX_SPQ_PENDING);
    sc->spq_prod_idx = 0;
    sc->dsb_sp_prod = &sc->def_sb->sp_sb.index_values[HC_SP_INDEX_ETH_DEF_CONS];
    sc->spq_prod_bd = sc->spq;
    sc->spq_last_bd = (sc->spq_prod_bd + MAX_SP_DESC_CNT);
}