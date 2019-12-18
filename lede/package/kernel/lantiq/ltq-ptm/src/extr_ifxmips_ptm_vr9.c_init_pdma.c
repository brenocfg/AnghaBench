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

/* Variables and functions */
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDMA_CFG ; 
 int /*<<< orphan*/  PDMA_RX_CTX_CFG ; 
 int /*<<< orphan*/  PDMA_RX_DELAY_CFG ; 
 int /*<<< orphan*/  PDMA_RX_MAX_LEN_REG ; 
 int /*<<< orphan*/  PDMA_TX_CTX_CFG ; 
 int /*<<< orphan*/  SAR_CRC_SIZE_CFG ; 
 int /*<<< orphan*/  SAR_MODE_CFG ; 
 int /*<<< orphan*/  SAR_PDMA_RX_CMDBUF_CFG ; 
 int /*<<< orphan*/  SAR_PDMA_TX_CMDBUF_CFG ; 
 int /*<<< orphan*/  SAR_POLY_CFG_SET0 ; 
 int /*<<< orphan*/  SAR_POLY_CFG_SET1 ; 
 int /*<<< orphan*/  SAR_POLY_CFG_SET2 ; 
 int /*<<< orphan*/  SAR_RX_CTX_CFG ; 
 int /*<<< orphan*/  SAR_TX_CTX_CFG ; 

__attribute__((used)) static inline void init_pdma(void)
{
    IFX_REG_W32(0x00000001, PDMA_CFG);
    IFX_REG_W32(0x00082C00, PDMA_RX_CTX_CFG);
    IFX_REG_W32(0x00081B00, PDMA_TX_CTX_CFG);
    IFX_REG_W32(0x02040604, PDMA_RX_MAX_LEN_REG);
    IFX_REG_W32(0x000F003F, PDMA_RX_DELAY_CFG);

    IFX_REG_W32(0x00000011, SAR_MODE_CFG);
    IFX_REG_W32(0x00082A00, SAR_RX_CTX_CFG);
    IFX_REG_W32(0x00082E00, SAR_TX_CTX_CFG);
    IFX_REG_W32(0x00001021, SAR_POLY_CFG_SET0);
    IFX_REG_W32(0x1EDC6F41, SAR_POLY_CFG_SET1);
    IFX_REG_W32(0x04C11DB7, SAR_POLY_CFG_SET2);
    IFX_REG_W32(0x00000F3E, SAR_CRC_SIZE_CFG);

    IFX_REG_W32(0x01001900, SAR_PDMA_RX_CMDBUF_CFG);
    IFX_REG_W32(0x01001A00, SAR_PDMA_TX_CMDBUF_CFG);
}