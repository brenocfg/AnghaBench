#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {TYPE_1__* bar; int /*<<< orphan*/  spq_prod_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 size_t BAR0 ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  REG_WR16 (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 scalar_t__ XSTORM_SPQ_PROD_OFFSET (int) ; 
 int /*<<< orphan*/  bus_space_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline
void bxe_sp_prod_update(struct bxe_softc *sc)
{
    int func = SC_FUNC(sc);

    /*
     * Make sure that BD data is updated before writing the producer.
     * BD data is written to the memory, the producer is read from the
     * memory, thus we need a full memory barrier to ensure the ordering.
     */
    mb();

    REG_WR16(sc, (BAR_XSTRORM_INTMEM + XSTORM_SPQ_PROD_OFFSET(func)),
             sc->spq_prod_idx);

    bus_space_barrier(sc->bar[BAR0].tag, sc->bar[BAR0].handle, 0, 0,
                      BUS_SPACE_BARRIER_WRITE);
}