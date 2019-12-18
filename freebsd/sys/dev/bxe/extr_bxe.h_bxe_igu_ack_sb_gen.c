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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct igu_regular {int sb_id_and_flags; int /*<<< orphan*/  member_0; } ;
struct bxe_softc {TYPE_1__* bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int IGU_REGULAR_BUPDATE_SHIFT ; 
 int IGU_REGULAR_ENABLE_INT_SHIFT ; 
 int IGU_REGULAR_SB_INDEX_SHIFT ; 
 int IGU_REGULAR_SEGMENT_ACCESS_SHIFT ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void
bxe_igu_ack_sb_gen(struct bxe_softc *sc,
                   uint8_t          igu_sb_id,
                   uint8_t          segment,
                   uint16_t         index,
                   uint8_t          op,
                   uint8_t          update,
                   uint32_t         igu_addr)
{
    struct igu_regular cmd_data = {0};

    cmd_data.sb_id_and_flags =
        ((index << IGU_REGULAR_SB_INDEX_SHIFT) |
         (segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
         (update << IGU_REGULAR_BUPDATE_SHIFT) |
         (op << IGU_REGULAR_ENABLE_INT_SHIFT));

    BLOGD(sc, DBG_INTR, "write 0x%08x to IGU addr 0x%x\n",
            cmd_data.sb_id_and_flags, igu_addr);
    REG_WR(sc, igu_addr, cmd_data.sb_id_and_flags);

    /* Make sure that ACK is written */
    bus_space_barrier(sc->bar[0].tag, sc->bar[0].handle, 0, 0,
                      BUS_SPACE_BARRIER_WRITE);
    mb();
}