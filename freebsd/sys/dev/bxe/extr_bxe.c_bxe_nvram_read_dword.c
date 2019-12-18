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
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MCPR_NVM_ADDR_NVM_ADDR_VALUE ; 
 int MCPR_NVM_COMMAND_DOIT ; 
 int MCPR_NVM_COMMAND_DONE ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_ADDR ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_COMMAND ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_READ ; 
 int NVRAM_TIMEOUT_COUNT ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int htobe32 (int) ; 

__attribute__((used)) static int
bxe_nvram_read_dword(struct bxe_softc *sc,
                     uint32_t         offset,
                     uint32_t         *ret_val,
                     uint32_t         cmd_flags)
{
    int count, i, rc;
    uint32_t val;

    /* build the command word */
    cmd_flags |= MCPR_NVM_COMMAND_DOIT;

    /* need to clear DONE bit separately */
    REG_WR(sc, MCP_REG_MCPR_NVM_COMMAND, MCPR_NVM_COMMAND_DONE);

    /* address of the NVRAM to read from */
    REG_WR(sc, MCP_REG_MCPR_NVM_ADDR,
           (offset & MCPR_NVM_ADDR_NVM_ADDR_VALUE));

    /* issue a read command */
    REG_WR(sc, MCP_REG_MCPR_NVM_COMMAND, cmd_flags);

    /* adjust timeout for emulation/FPGA */
    count = NVRAM_TIMEOUT_COUNT;
    if (CHIP_REV_IS_SLOW(sc)) {
        count *= 100;
    }

    /* wait for completion */
    *ret_val = 0;
    rc = -1;
    for (i = 0; i < count; i++) {
        DELAY(5);
        val = REG_RD(sc, MCP_REG_MCPR_NVM_COMMAND);

        if (val & MCPR_NVM_COMMAND_DONE) {
            val = REG_RD(sc, MCP_REG_MCPR_NVM_READ);
            /* we read nvram data in cpu order
             * but ethtool sees it as an array of bytes
             * converting to big-endian will do the work
             */
            *ret_val = htobe32(val);
            rc = 0;
            break;
        }
    }

    if (rc == -1) {
        BLOGE(sc, "nvram read timeout expired "
            "(offset 0x%x cmd_flags 0x%x val 0x%x)\n",
            offset, cmd_flags, val);
    }

    return (rc);
}