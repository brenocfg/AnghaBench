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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int BXE_PATH0_LOAD_CNT_MASK ; 
 int BXE_PATH0_LOAD_CNT_SHIFT ; 
 int BXE_PATH1_LOAD_CNT_MASK ; 
 int BXE_PATH1_LOAD_CNT_SHIFT ; 
 int /*<<< orphan*/  BXE_RECOVERY_GLOB_REG ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RECOVERY_REG ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int SC_ABS_FUNC (struct bxe_softc*) ; 
 scalar_t__ SC_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
bxe_clear_pf_load(struct bxe_softc *sc)
{
    uint32_t val1, val;
    uint32_t mask = SC_PATH(sc) ? BXE_PATH1_LOAD_CNT_MASK :
                                  BXE_PATH0_LOAD_CNT_MASK;
    uint32_t shift = SC_PATH(sc) ? BXE_PATH1_LOAD_CNT_SHIFT :
                                   BXE_PATH0_LOAD_CNT_SHIFT;

    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_RECOVERY_REG);
    val = REG_RD(sc, BXE_RECOVERY_GLOB_REG);
    BLOGD(sc, DBG_LOAD, "Old GEN_REG_VAL=0x%08x\n", val);

    /* get the current counter value */
    val1 = (val & mask) >> shift;

    /* clear bit of that PF */
    val1 &= ~(1 << SC_ABS_FUNC(sc));

    /* clear the old value */
    val &= ~mask;

    /* set the new one */
    val |= ((val1 << shift) & mask);

    REG_WR(sc, BXE_RECOVERY_GLOB_REG, val);
    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_RECOVERY_REG);
    return (val1 != 0);
}