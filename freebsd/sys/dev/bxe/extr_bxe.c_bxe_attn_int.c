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
typedef  int uint32_t ;
struct bxe_softc {int attn_state; TYPE_2__* def_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  attn_bits_ack; int /*<<< orphan*/  attn_bits; } ;
struct TYPE_4__ {TYPE_1__ atten_status_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int /*<<< orphan*/  bxe_attn_int_asserted (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_attn_int_deasserted (struct bxe_softc*,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_attn_int(struct bxe_softc *sc)
{
    /* read local copy of bits */
    uint32_t attn_bits = le32toh(sc->def_sb->atten_status_block.attn_bits);
    uint32_t attn_ack = le32toh(sc->def_sb->atten_status_block.attn_bits_ack);
    uint32_t attn_state = sc->attn_state;

    /* look for changed bits */
    uint32_t asserted   =  attn_bits & ~attn_ack & ~attn_state;
    uint32_t deasserted = ~attn_bits &  attn_ack &  attn_state;

    BLOGD(sc, DBG_INTR,
          "attn_bits 0x%08x attn_ack 0x%08x asserted 0x%08x deasserted 0x%08x\n",
          attn_bits, attn_ack, asserted, deasserted);

    if (~(attn_bits ^ attn_ack) & (attn_bits ^ attn_state)) {
        BLOGE(sc, "BAD attention state\n");
    }

    /* handle bits that were raised */
    if (asserted) {
        bxe_attn_int_asserted(sc, asserted);
    }

    if (deasserted) {
        bxe_attn_int_deasserted(sc, deasserted);
    }
}