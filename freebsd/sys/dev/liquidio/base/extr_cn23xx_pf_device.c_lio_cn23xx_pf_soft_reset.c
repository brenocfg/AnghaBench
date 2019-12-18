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
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_RST_SOFT_RST ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_SCRATCH1 ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_WIN_WR_MASK_REG ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_mdelay (int) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lio_cn23xx_pf_soft_reset(struct octeon_device *oct)
{

	lio_write_csr64(oct, LIO_CN23XX_SLI_WIN_WR_MASK_REG, 0xFF);

	lio_dev_dbg(oct, "BIST enabled for CN23XX soft reset\n");

	lio_write_csr64(oct, LIO_CN23XX_SLI_SCRATCH1, 0x1234ULL);

	/* Initiate chip-wide soft reset */
	lio_pci_readq(oct, LIO_CN23XX_RST_SOFT_RST);
	lio_pci_writeq(oct, 1, LIO_CN23XX_RST_SOFT_RST);

	/* Wait for 100ms as Octeon resets. */
	lio_mdelay(100);

	if (lio_read_csr64(oct, LIO_CN23XX_SLI_SCRATCH1)) {
		lio_dev_err(oct, "Soft reset failed\n");
		return (1);
	}

	lio_dev_dbg(oct, "Reset completed\n");

	/* restore the  reset value */
	lio_write_csr64(oct, LIO_CN23XX_SLI_WIN_WR_MASK_REG, 0xFF);

	return (0);
}