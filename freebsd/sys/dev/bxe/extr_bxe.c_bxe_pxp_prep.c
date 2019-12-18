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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  PXP2_REG_RD_START_INIT ; 
 int /*<<< orphan*/  PXP2_REG_RQ_RBC_DONE ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
bxe_pxp_prep(struct bxe_softc *sc)
{
    if (!CHIP_IS_E1(sc)) {
        REG_WR(sc, PXP2_REG_RD_START_INIT, 0);
        REG_WR(sc, PXP2_REG_RQ_RBC_DONE, 0);
        wmb();
    }
}