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
 int /*<<< orphan*/  CFC_REG_WEAK_ENABLE_PF ; 
 int /*<<< orphan*/  IGU_PF_CONF_FUNC_EN ; 
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION ; 
 int /*<<< orphan*/  PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_pf_disable(struct bxe_softc *sc)
{
    uint32_t val = REG_RD(sc, IGU_REG_PF_CONFIGURATION);

    val &= ~IGU_PF_CONF_FUNC_EN;

    REG_WR(sc, IGU_REG_PF_CONFIGURATION, val);
    REG_WR(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);
    REG_WR(sc, CFC_REG_WEAK_ENABLE_PF, 0);
}