#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* lo; void* hi; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
union event_ring_elem {TYPE_2__ next_page; } ;
struct TYPE_8__ {scalar_t__ paddr; } ;
struct bxe_softc {int /*<<< orphan*/  eq_spq_left; TYPE_5__* def_sb; int /*<<< orphan*/ * eq_cons_sb; int /*<<< orphan*/  eq_prod; scalar_t__ eq_cons; TYPE_3__ eq_dma; union event_ring_elem* eq; } ;
struct TYPE_9__ {int /*<<< orphan*/ * index_values; } ;
struct TYPE_10__ {TYPE_4__ sp_sb; } ;

/* Variables and functions */
 int BCM_PAGE_SIZE ; 
 int EQ_DESC_CNT_PAGE ; 
 size_t HC_SP_INDEX_EQ_CONS ; 
 scalar_t__ MAX_SPQ_PENDING ; 
 scalar_t__ MAX_SP_DESC_CNT ; 
 int /*<<< orphan*/  NUM_EQ_DESC ; 
 int NUM_EQ_PAGES ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 int /*<<< orphan*/  atomic_store_rel_long (int /*<<< orphan*/ *,scalar_t__) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_init_eq_ring(struct bxe_softc *sc)
{
    union event_ring_elem *elem;
    int i;

    for (i = 1; i <= NUM_EQ_PAGES; i++) {
        elem = &sc->eq[EQ_DESC_CNT_PAGE * i - 1];

        elem->next_page.addr.hi = htole32(U64_HI(sc->eq_dma.paddr +
                                                 BCM_PAGE_SIZE *
                                                 (i % NUM_EQ_PAGES)));
        elem->next_page.addr.lo = htole32(U64_LO(sc->eq_dma.paddr +
                                                 BCM_PAGE_SIZE *
                                                 (i % NUM_EQ_PAGES)));
    }

    sc->eq_cons    = 0;
    sc->eq_prod    = NUM_EQ_DESC;
    sc->eq_cons_sb = &sc->def_sb->sp_sb.index_values[HC_SP_INDEX_EQ_CONS];

    atomic_store_rel_long(&sc->eq_spq_left,
                          (min((MAX_SP_DESC_CNT - MAX_SPQ_PENDING),
                               NUM_EQ_DESC) - 1));
}