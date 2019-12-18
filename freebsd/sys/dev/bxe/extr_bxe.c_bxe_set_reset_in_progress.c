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
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_PATH0_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BXE_PATH1_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BXE_RECOVERY_GLOB_REG ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RECOVERY_REG ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SC_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_set_reset_in_progress(struct bxe_softc *sc)
{
    uint32_t val;
    uint32_t bit = SC_PATH(sc) ? BXE_PATH1_RST_IN_PROG_BIT :
                                 BXE_PATH0_RST_IN_PROG_BIT;

    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_RECOVERY_REG);

    val = REG_RD(sc, BXE_RECOVERY_GLOB_REG);
    /* Set the bit */
    val |= bit;
    REG_WR(sc, BXE_RECOVERY_GLOB_REG, val);

    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_RECOVERY_REG);
}