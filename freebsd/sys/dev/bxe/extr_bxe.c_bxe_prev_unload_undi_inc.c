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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ BXE_PREV_UNDI_BD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_PREV_UNDI_PROD (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BXE_PREV_UNDI_PROD_ADDR (scalar_t__) ; 
 scalar_t__ BXE_PREV_UNDI_RCQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_prev_unload_undi_inc(struct bxe_softc *sc,
                         uint8_t          port,
                         uint8_t          inc)
{
    uint16_t rcq, bd;
    uint32_t tmp_reg = REG_RD(sc, BXE_PREV_UNDI_PROD_ADDR(port));

    rcq = BXE_PREV_UNDI_RCQ(tmp_reg) + inc;
    bd = BXE_PREV_UNDI_BD(tmp_reg) + inc;

    tmp_reg = BXE_PREV_UNDI_PROD(rcq, bd);
    REG_WR(sc, BXE_PREV_UNDI_PROD_ADDR(port), tmp_reg);

    BLOGD(sc, DBG_LOAD,
          "UNDI producer [%d] rings bd -> 0x%04x, rcq -> 0x%04x\n",
          port, bd, rcq);
}