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
 int MAX_RX_RINGS ; 
 int /*<<< orphan*/  Q81_CTL_INTR_ENABLE ; 
 int /*<<< orphan*/  READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qls_get_intr_states(qla_host_t *ha, uint32_t *buf)
{
	int i;

	for (i = 0; i < MAX_RX_RINGS; i++, buf++) {

		WRITE_REG32(ha, Q81_CTL_INTR_ENABLE, (0x037f0300 + i));

		*buf = READ_REG32(ha, Q81_CTL_INTR_ENABLE);
	}
}