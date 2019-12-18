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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQM_DBELL_OVF_HI_ENA_W1S ; 
 int /*<<< orphan*/  AQM_DBELL_OVF_LO_ENA_W1S ; 
 int /*<<< orphan*/  AQM_DMA_RD_ERR_HI_ENA_W1S ; 
 int /*<<< orphan*/  AQM_DMA_RD_ERR_LO_ENA_W1S ; 
 int /*<<< orphan*/  AQM_EXEC_ERR_HI_ENA_W1S ; 
 int /*<<< orphan*/  AQM_EXEC_ERR_LO_ENA_W1S ; 
 int /*<<< orphan*/  AQM_EXEC_NA_HI_ENA_W1S ; 
 int /*<<< orphan*/  AQM_EXEC_NA_LO_ENA_W1S ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void enable_aqm_interrupts(struct nitrox_device *ndev)
{
	/* clear interrupt enable bits */
	nitrox_write_csr(ndev, AQM_DBELL_OVF_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_DBELL_OVF_HI_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_DMA_RD_ERR_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_DMA_RD_ERR_HI_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_EXEC_NA_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_EXEC_NA_HI_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_EXEC_ERR_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, AQM_EXEC_ERR_HI_ENA_W1S, (~0ULL));
}