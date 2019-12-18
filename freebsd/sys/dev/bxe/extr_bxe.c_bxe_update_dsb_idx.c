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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ running_index; } ;
struct TYPE_4__ {scalar_t__ attn_bits_index; } ;
struct host_sp_status_block {TYPE_1__ sp_sb; TYPE_2__ atten_status_block; } ;
struct bxe_softc {scalar_t__ def_att_idx; scalar_t__ def_idx; struct host_sp_status_block* def_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_DEF_SB_ATT_IDX ; 
 int /*<<< orphan*/  BXE_DEF_SB_IDX ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static uint16_t
bxe_update_dsb_idx(struct bxe_softc *sc)
{
    struct host_sp_status_block *def_sb = sc->def_sb;
    uint16_t rc = 0;

    mb(); /* status block is written to by the chip */

    if (sc->def_att_idx != def_sb->atten_status_block.attn_bits_index) {
        sc->def_att_idx = def_sb->atten_status_block.attn_bits_index;
        rc |= BXE_DEF_SB_ATT_IDX;
    }

    if (sc->def_idx != def_sb->sp_sb.running_index) {
        sc->def_idx = def_sb->sp_sb.running_index;
        rc |= BXE_DEF_SB_IDX;
    }

    mb();

    return (rc);
}