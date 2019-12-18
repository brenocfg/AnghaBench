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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bxe_softc {scalar_t__ igu_dsb_id; TYPE_1__ devinfo; } ;

/* Variables and functions */
 scalar_t__ ATTENTION_ID ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bxe_softc*) ; 
 scalar_t__ IGU_SEG_ACCESS_ATTN ; 
 scalar_t__ IGU_SEG_ACCESS_DEF ; 
 scalar_t__ INT_BLOCK_HC ; 
 int /*<<< orphan*/  bxe_hc_ack_sb (struct bxe_softc*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bxe_igu_ack_sb (struct bxe_softc*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
bxe_ack_sb(struct bxe_softc *sc,
           uint8_t          igu_sb_id,
           uint8_t          storm,
           uint16_t         index,
           uint8_t          op,
           uint8_t          update)
{
    if (sc->devinfo.int_block == INT_BLOCK_HC)
        bxe_hc_ack_sb(sc, igu_sb_id, storm, index, op, update);
    else {
        uint8_t segment;
        if (CHIP_INT_MODE_IS_BC(sc)) {
            segment = storm;
        } else if (igu_sb_id != sc->igu_dsb_id) {
            segment = IGU_SEG_ACCESS_DEF;
        } else if (storm == ATTENTION_ID) {
            segment = IGU_SEG_ACCESS_ATTN;
        } else {
            segment = IGU_SEG_ACCESS_DEF;
        }
        bxe_igu_ack_sb(sc, igu_sb_id, segment, index, op, update);
    }
}