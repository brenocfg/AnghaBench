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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bxe_softc {scalar_t__ interrupt_mode; int intr_count; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_INTR ; 
 scalar_t__ FALSE ; 
 int HC_CONFIG_0_REG_ATTN_BIT_EN_0 ; 
 int HC_CONFIG_0_REG_INT_LINE_EN_0 ; 
 int HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 ; 
 int HC_CONFIG_0_REG_SINGLE_ISR_EN_0 ; 
 int HC_REG_CONFIG_0 ; 
 int HC_REG_CONFIG_1 ; 
 int HC_REG_INT_MASK ; 
 int HC_REG_LEADING_EDGE_0 ; 
 int HC_REG_TRAILING_EDGE_0 ; 
 scalar_t__ INTR_MODE_MSI ; 
 scalar_t__ INTR_MODE_MSIX ; 
 scalar_t__ IS_MF (struct bxe_softc*) ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int SC_VN (struct bxe_softc*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
bxe_hc_int_enable(struct bxe_softc *sc)
{
    int port = SC_PORT(sc);
    uint32_t addr = (port) ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0;
    uint32_t val = REG_RD(sc, addr);
    uint8_t msix = (sc->interrupt_mode == INTR_MODE_MSIX) ? TRUE : FALSE;
    uint8_t single_msix = ((sc->interrupt_mode == INTR_MODE_MSIX) &&
                           (sc->intr_count == 1)) ? TRUE : FALSE;
    uint8_t msi = (sc->interrupt_mode == INTR_MODE_MSI) ? TRUE : FALSE;

    if (msix) {
        val &= ~(HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
                 HC_CONFIG_0_REG_INT_LINE_EN_0);
        val |= (HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
                HC_CONFIG_0_REG_ATTN_BIT_EN_0);
        if (single_msix) {
            val |= HC_CONFIG_0_REG_SINGLE_ISR_EN_0;
        }
    } else if (msi) {
        val &= ~HC_CONFIG_0_REG_INT_LINE_EN_0;
        val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
                HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
                HC_CONFIG_0_REG_ATTN_BIT_EN_0);
    } else {
        val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
                HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
                HC_CONFIG_0_REG_INT_LINE_EN_0 |
                HC_CONFIG_0_REG_ATTN_BIT_EN_0);

        if (!CHIP_IS_E1(sc)) {
            BLOGD(sc, DBG_INTR, "write %x to HC %d (addr 0x%x)\n",
                  val, port, addr);

            REG_WR(sc, addr, val);

            val &= ~HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0;
        }
    }

    if (CHIP_IS_E1(sc)) {
        REG_WR(sc, (HC_REG_INT_MASK + port*4), 0x1FFFF);
    }

    BLOGD(sc, DBG_INTR, "write %x to HC %d (addr 0x%x) mode %s\n",
          val, port, addr, ((msix) ? "MSI-X" : ((msi) ? "MSI" : "INTx")));

    REG_WR(sc, addr, val);

    /* ensure that HC_CONFIG is written before leading/trailing edge config */
    mb();

    if (!CHIP_IS_E1(sc)) {
        /* init leading/trailing edge */
        if (IS_MF(sc)) {
            val = (0xee0f | (1 << (SC_VN(sc) + 4)));
            if (sc->port.pmf) {
                /* enable nig and gpio3 attention */
                val |= 0x1100;
            }
        } else {
            val = 0xffff;
        }

        REG_WR(sc, (HC_REG_TRAILING_EDGE_0 + port*8), val);
        REG_WR(sc, (HC_REG_LEADING_EDGE_0 + port*8), val);
    }

    /* make sure that interrupts are indeed enabled from here on */
    mb();
}