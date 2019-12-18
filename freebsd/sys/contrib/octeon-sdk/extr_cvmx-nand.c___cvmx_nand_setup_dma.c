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
struct TYPE_2__ {int en; int rw; int size; scalar_t__ adr; scalar_t__ clr; } ;
union cvmx_mio_ndf_dma_cfg {scalar_t__ u64; TYPE_1__ s; } ;
typedef  scalar_t__ uint64_t ;
typedef  int ULL ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIO_NDF_DMA_CFG ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN_NOTHING () ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void __cvmx_nand_setup_dma(int chip, int is_write, uint64_t buffer_address, int buffer_length)
{
    union cvmx_mio_ndf_dma_cfg ndf_dma_cfg;
    CVMX_NAND_LOG_CALLED();
    CVMX_NAND_LOG_PARAM("%d", chip);
    CVMX_NAND_LOG_PARAM("%d", is_write);
    CVMX_NAND_LOG_PARAM("0x%llx", (ULL)buffer_address);
    CVMX_NAND_LOG_PARAM("%d", buffer_length);
    ndf_dma_cfg.u64 = 0;
    ndf_dma_cfg.s.en = 1;
    ndf_dma_cfg.s.rw = is_write; /* One means DMA reads from memory and writes to flash */
    ndf_dma_cfg.s.clr = 0;
    ndf_dma_cfg.s.size = ((buffer_length + 7) >> 3) - 1;
    ndf_dma_cfg.s.adr = buffer_address;
    CVMX_SYNCWS;
    cvmx_write_csr(CVMX_MIO_NDF_DMA_CFG, ndf_dma_cfg.u64);
    CVMX_NAND_RETURN_NOTHING();
}