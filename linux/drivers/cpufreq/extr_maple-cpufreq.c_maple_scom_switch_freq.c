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
struct TYPE_2__ {unsigned long frequency; } ;

/* Variables and functions */
 unsigned long PCR_HILO_SELECT ; 
 unsigned long PCR_SPEED_SHIFT ; 
 unsigned long PSR_CMD_COMPLETED ; 
 unsigned long PSR_CMD_RECEIVED ; 
 unsigned long PSR_CUR_SPEED_SHIFT ; 
 int /*<<< orphan*/  SCOM_PCR ; 
 int /*<<< orphan*/  SCOM_PSR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__* maple_cpu_freqs ; 
 int maple_pmode_cur ; 
 unsigned long* maple_pmode_data ; 
 unsigned long ppc_proc_freq ; 
 unsigned long scom970_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scom970_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int maple_scom_switch_freq(int speed_mode)
{
	unsigned long flags;
	int to;

	local_irq_save(flags);

	/* Clear PCR high */
	scom970_write(SCOM_PCR, 0);
	/* Clear PCR low */
	scom970_write(SCOM_PCR, PCR_HILO_SELECT | 0);
	/* Set PCR low */
	scom970_write(SCOM_PCR, PCR_HILO_SELECT |
		      maple_pmode_data[speed_mode]);

	/* Wait for completion */
	for (to = 0; to < 10; to++) {
		unsigned long psr = scom970_read(SCOM_PSR);

		if ((psr & PSR_CMD_RECEIVED) == 0 &&
		    (((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (maple_pmode_data[speed_mode] >> PCR_SPEED_SHIFT)) & 0x3)
		    == 0)
			break;
		if (psr & PSR_CMD_COMPLETED)
			break;
		udelay(100);
	}

	local_irq_restore(flags);

	maple_pmode_cur = speed_mode;
	ppc_proc_freq = maple_cpu_freqs[speed_mode].frequency * 1000ul;

	return 0;
}