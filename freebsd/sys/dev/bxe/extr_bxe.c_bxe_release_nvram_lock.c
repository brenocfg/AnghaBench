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
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_NVRAM ; 
 int MCPR_NVM_SW_ARB_ARB_ARB1 ; 
 int MCPR_NVM_SW_ARB_ARB_REQ_CLR1 ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_SW_ARB ; 
 int NVRAM_TIMEOUT_COUNT ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_release_nvram_lock(struct bxe_softc *sc)
{
    int port = SC_PORT(sc);
    int count, i;
    uint32_t val = 0;

    /* adjust timeout for emulation/FPGA */
    count = NVRAM_TIMEOUT_COUNT;
    if (CHIP_REV_IS_SLOW(sc)) {
        count *= 100;
    }

    /* relinquish nvram interface */
    REG_WR(sc, MCP_REG_MCPR_NVM_SW_ARB,
           (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << port));

    for (i = 0; i < count*10; i++) {
        val = REG_RD(sc, MCP_REG_MCPR_NVM_SW_ARB);
        if (!(val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port))) {
            break;
        }

        DELAY(5);
    }

    if (val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port)) {
        BLOGE(sc, "Cannot free access to nvram interface "
            "port %d val 0x%x (MCPR_NVM_SW_ARB_ARB_ARB1 << port)\n",
            port, val);
        return (-1);
    }

    /* release HW lock: protect against other PFs in PF Direct Assignment */
    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_NVRAM);

    return (0);
}