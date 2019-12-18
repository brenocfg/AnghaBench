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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int IGU_PF_CONF_ATTN_BIT_EN ; 
 int IGU_PF_CONF_INT_LINE_EN ; 
 int IGU_PF_CONF_MSI_MSIX_EN ; 
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
bxe_igu_int_disable(struct bxe_softc *sc)
{
    uint32_t val = REG_RD(sc, IGU_REG_PF_CONFIGURATION);

    val &= ~(IGU_PF_CONF_MSI_MSIX_EN |
             IGU_PF_CONF_INT_LINE_EN |
             IGU_PF_CONF_ATTN_BIT_EN);

    BLOGD(sc, DBG_INTR, "write %x to IGU\n", val);

    /* flush all outstanding writes */
    mb();

    REG_WR(sc, IGU_REG_PF_CONFIGURATION, val);
    if (REG_RD(sc, IGU_REG_PF_CONFIGURATION) != val) {
        BLOGE(sc, "proper val not read from IGU!\n");
    }
}