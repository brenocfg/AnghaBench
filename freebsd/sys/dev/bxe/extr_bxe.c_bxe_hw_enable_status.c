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
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFC_REG_WEAK_ENABLE_PF ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSIX_EN ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSIX_FUNC_MASK ; 
 int /*<<< orphan*/  IGU_REG_PCI_PF_MSI_EN ; 
 int /*<<< orphan*/  PBF_REG_DISABLE_PF ; 
 int /*<<< orphan*/  PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR ; 
 int /*<<< orphan*/  PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_hw_enable_status(struct bxe_softc *sc)
{
    uint32_t val;

    val = REG_RD(sc, CFC_REG_WEAK_ENABLE_PF);
    BLOGD(sc, DBG_LOAD, "CFC_REG_WEAK_ENABLE_PF is 0x%x\n", val);

    val = REG_RD(sc, PBF_REG_DISABLE_PF);
    BLOGD(sc, DBG_LOAD, "PBF_REG_DISABLE_PF is 0x%x\n", val);

    val = REG_RD(sc, IGU_REG_PCI_PF_MSI_EN);
    BLOGD(sc, DBG_LOAD, "IGU_REG_PCI_PF_MSI_EN is 0x%x\n", val);

    val = REG_RD(sc, IGU_REG_PCI_PF_MSIX_EN);
    BLOGD(sc, DBG_LOAD, "IGU_REG_PCI_PF_MSIX_EN is 0x%x\n", val);

    val = REG_RD(sc, IGU_REG_PCI_PF_MSIX_FUNC_MASK);
    BLOGD(sc, DBG_LOAD, "IGU_REG_PCI_PF_MSIX_FUNC_MASK is 0x%x\n", val);

    val = REG_RD(sc, PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR);
    BLOGD(sc, DBG_LOAD, "PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR is 0x%x\n", val);

    val = REG_RD(sc, PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR);
    BLOGD(sc, DBG_LOAD, "PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR is 0x%x\n", val);

    val = REG_RD(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER);
    BLOGD(sc, DBG_LOAD, "PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER is 0x%x\n", val);
}