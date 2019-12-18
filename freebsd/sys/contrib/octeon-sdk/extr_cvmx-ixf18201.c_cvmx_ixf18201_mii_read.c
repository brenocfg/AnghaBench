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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IXF_REG_MDI_CMD_ADDR1 ; 
 int /*<<< orphan*/  IXF_REG_MDI_RD_WR1 ; 
 int cvmx_ixf18201_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_ixf18201_write32 (int /*<<< orphan*/ ,int) ; 

int cvmx_ixf18201_mii_read(int mii_addr, int mmd, uint16_t reg)
{
    uint32_t cmd_val = 0;


    cmd_val = reg;
    cmd_val |= 0x0 << 26;  // Set address operation
    cmd_val |= (mii_addr & 0x1f) << 21;  // Set PHY addr
    cmd_val |= (mmd & 0x1f) << 16;  // Set MMD
    cmd_val |= 1 << 30;   // Do operation
    cmd_val |= 1 << 31;   // enable in progress bit



    /* Set up address */
    cvmx_ixf18201_write32(IXF_REG_MDI_CMD_ADDR1, cmd_val);

    while (cvmx_ixf18201_read32(IXF_REG_MDI_CMD_ADDR1) & ( 1 << 30))
        ;  /* Wait for operation to complete */

    /* Do read operation */
    cmd_val = 0;
    cmd_val |= 0x3 << 26;  // Set read operation
    cmd_val |= (mii_addr & 0x1f) << 21;  // Set PHY addr
    cmd_val |= (mmd & 0x1f) << 16;  // Set MMD
    cmd_val |= 1 << 30;   // Do operation
    cmd_val |= 1 << 31;   // enable in progress bit
    cvmx_ixf18201_write32(IXF_REG_MDI_CMD_ADDR1, cmd_val);

    while (cvmx_ixf18201_read32(IXF_REG_MDI_CMD_ADDR1) & ( 1 << 30))
        ;  /* Wait for operation to complete */

    cmd_val = cvmx_ixf18201_read32(IXF_REG_MDI_RD_WR1);

    return(cmd_val >> 16);

}