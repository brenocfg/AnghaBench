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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_CTL_CNA_ENH_TX_SCHD ; 
 int /*<<< orphan*/  Q81_CTL_NIC_ENH_TX_SCHD ; 
 int /*<<< orphan*/  READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qls_get_ets_regs(qla_host_t *ha, uint32_t *buf)
{
	int ret = 0;
	int i;

	for(i = 0; i < 8; i ++, buf ++) {
		WRITE_REG32(ha, Q81_CTL_NIC_ENH_TX_SCHD, \
			((i << 29) | 0x08000000));
		*buf = READ_REG32(ha, Q81_CTL_NIC_ENH_TX_SCHD);
	}

	for(i = 0; i < 2; i ++, buf ++) {
		WRITE_REG32(ha, Q81_CTL_CNA_ENH_TX_SCHD, \
			((i << 29) | 0x08000000));
		*buf = READ_REG32(ha, Q81_CTL_CNA_ENH_TX_SCHD);
	}

	return ret;
}