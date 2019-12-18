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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CLOCK ; 
 int /*<<< orphan*/  PCI_CLOCK ; 
 int /*<<< orphan*/  SYS_CLOCK ; 
 int /*<<< orphan*/  XGM_CLOCK ; 
 int /*<<< orphan*/ * qls_get_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qls_wr_mpi_reg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
qls_get_probe_dump(qla_host_t *ha, uint32_t *buf)
{

	uint8_t sys_clock_valid_modules[0x20] = {
		1,   // 0x00
		1,   // 0x01
		1,   // 0x02
		0,   // 0x03
		1,   // 0x04
		1,   // 0x05
		1,   // 0x06
		1,   // 0x07
		1,   // 0x08
		1,   // 0x09
		1,   // 0x0A
		1,   // 0x0B
		1,   // 0x0C
		1,   // 0x0D
		1,   // 0x0E
		0,   // 0x0F
		1,   // 0x10
		1,   // 0x11
		1,   // 0x12
		1,   // 0x13
		0,   // 0x14
		0,   // 0x15
		0,   // 0x16
		0,   // 0x17
		0,   // 0x18
		0,   // 0x19
		0,   // 0x1A
		0,   // 0x1B
		0,   // 0x1C
		0,   // 0x1D
		0,   // 0x1E
		0    // 0x1F
	};


	uint8_t pci_clock_valid_modules[0x20] = {
		1,   // 0x00
		0,   // 0x01
		0,   // 0x02
		0,   // 0x03
		0,   // 0x04
		0,   // 0x05
		1,   // 0x06
		1,   // 0x07
		0,   // 0x08
		0,   // 0x09
		0,   // 0x0A
		0,   // 0x0B
		0,   // 0x0C
		0,   // 0x0D
		1,   // 0x0E
		0,   // 0x0F
		0,   // 0x10
		0,   // 0x11
		0,   // 0x12
		0,   // 0x13
		0,   // 0x14
		0,   // 0x15
		0,   // 0x16
		0,   // 0x17
		0,   // 0x18
		0,   // 0x19
		0,   // 0x1A
		0,   // 0x1B
		0,   // 0x1C
		0,   // 0x1D
		0,   // 0x1E
		0    // 0x1F
	};


	uint8_t xgm_clock_valid_modules[0x20] = {
		1,   // 0x00
		0,   // 0x01
		0,   // 0x02
		1,   // 0x03
		0,   // 0x04
		0,   // 0x05
		0,   // 0x06
		0,   // 0x07
		1,   // 0x08
		1,   // 0x09
		0,   // 0x0A
		0,   // 0x0B
		1,   // 0x0C
		1,   // 0x0D
		1,   // 0x0E
		0,   // 0x0F
		1,   // 0x10
		1,   // 0x11
		0,   // 0x12
		0,   // 0x13
		0,   // 0x14
		0,   // 0x15
		0,   // 0x16
		0,   // 0x17
		0,   // 0x18
		0,   // 0x19
		0,   // 0x1A
		0,   // 0x1B
		0,   // 0x1C
		0,   // 0x1D
		0,   // 0x1E
		0    // 0x1F
	};

	uint8_t fc_clock_valid_modules[0x20] = {
		1,   // 0x00
		0,   // 0x01
		0,   // 0x02
		0,   // 0x03
		0,   // 0x04
		0,   // 0x05
		0,   // 0x06
		0,   // 0x07
		0,   // 0x08
		0,   // 0x09
		0,   // 0x0A
		0,   // 0x0B
		1,   // 0x0C
		1,   // 0x0D
		0,   // 0x0E
		0,   // 0x0F
		0,   // 0x10
		0,   // 0x11
		0,   // 0x12
		0,   // 0x13
		0,   // 0x14
		0,   // 0x15
		0,   // 0x16
		0,   // 0x17
		0,   // 0x18
		0,   // 0x19
		0,   // 0x1A
		0,   // 0x1B
		0,   // 0x1C
		0,   // 0x1D
		0,   // 0x1E
		0    // 0x1F
	};

	qls_wr_mpi_reg(ha, 0x100e, 0x18a20000);

	buf = qls_get_probe(ha, SYS_CLOCK, sys_clock_valid_modules, buf);

	buf = qls_get_probe(ha, PCI_CLOCK, pci_clock_valid_modules, buf);

	buf = qls_get_probe(ha, XGM_CLOCK, xgm_clock_valid_modules, buf);

	buf = qls_get_probe(ha, FC_CLOCK, fc_clock_valid_modules, buf);

	return(0);
}