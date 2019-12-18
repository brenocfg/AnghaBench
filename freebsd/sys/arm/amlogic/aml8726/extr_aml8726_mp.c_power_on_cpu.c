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

/* Variables and functions */
 int AML_M8B_CPU_PWR_CNTL0_MODE_CPU1_MASK ; 
 int AML_M8B_CPU_PWR_CNTL1_PWR_CPU1 ; 
 int /*<<< orphan*/  AML_M8B_CPU_PWR_MEM_PD0_CPU1 ; 
 int /*<<< orphan*/  AML_M8B_CPU_PWR_MEM_PD0_REG ; 
 int AML_M8_CPU_CLK_CNTL_RESET_CPU1 ; 
 int AML_M8_CPU_PWR_CNTL0_ISO_CPU1 ; 
 int /*<<< orphan*/  AML_M8_CPU_PWR_CNTL0_REG ; 
 int AML_M8_CPU_PWR_CNTL1_MODE_CPU1_MASK ; 
 int /*<<< orphan*/  AML_M8_CPU_PWR_CNTL1_REG ; 
 int AML_SCU_CPU_PWR_STATUS_CPU1_MASK ; 
 int /*<<< orphan*/  AML_SCU_CPU_PWR_STATUS_REG ; 
 int /*<<< orphan*/  AML_SOC_CPU_CLK_CNTL_REG ; 
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int /*<<< orphan*/  AOBUS_BARRIER (int /*<<< orphan*/ ) ; 
 int AOBUS_READ_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AOBUS_WRITE_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CBUS_BARRIER (int /*<<< orphan*/ ) ; 
 int CBUS_READ_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBUS_WRITE_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SCU_BARRIER (int /*<<< orphan*/ ) ; 
 int SCU_READ_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_WRITE_4 (int /*<<< orphan*/ ,int) ; 
 int aml8726_soc_hw_rev ; 

__attribute__((used)) static void
power_on_cpu(int cpu)
{
	uint32_t scpsr;
	uint32_t value;

	if (cpu <= 0)
		return;

	/*
	 * Power on the CPU if the intricate details are known, otherwise
	 * just hope for the best (it may have already be powered on by
	 * the hardware / firmware).
	 */

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M8:
	case AML_SOC_HW_REV_M8B:
		/*
		 * Set the SCU power status for the CPU to normal mode.
		 */
		scpsr = SCU_READ_4(AML_SCU_CPU_PWR_STATUS_REG);
		scpsr &= ~(AML_SCU_CPU_PWR_STATUS_CPU1_MASK << ((cpu - 1) * 8));
		SCU_WRITE_4(AML_SCU_CPU_PWR_STATUS_REG, scpsr);
		SCU_BARRIER(AML_SCU_CPU_PWR_STATUS_REG);

		if (aml8726_soc_hw_rev == AML_SOC_HW_REV_M8B) {
			/*
			 * Reset may cause the current power status from the
			 * actual CPU to be written to the SCU (over-writing
			 * the value  we've just written) so set it to normal
			 * mode as well.
			 */
			 value = AOBUS_READ_4(AML_M8_CPU_PWR_CNTL0_REG);
			 value &= ~(AML_M8B_CPU_PWR_CNTL0_MODE_CPU1_MASK <<
			    ((cpu - 1) * 2));
			 AOBUS_WRITE_4(AML_M8_CPU_PWR_CNTL0_REG, value);
			 AOBUS_BARRIER(AML_M8_CPU_PWR_CNTL0_REG);
		 }

		DELAY(5);

		/*
		 * Assert reset.
		 */
		value = CBUS_READ_4(AML_SOC_CPU_CLK_CNTL_REG);
		value |= AML_M8_CPU_CLK_CNTL_RESET_CPU1 << (cpu - 1); 
		CBUS_WRITE_4(AML_SOC_CPU_CLK_CNTL_REG, value);
		CBUS_BARRIER(AML_SOC_CPU_CLK_CNTL_REG);

		if (aml8726_soc_hw_rev == AML_SOC_HW_REV_M8B) {
			/*
			 * Release RAM pull-down.
			 */
			 value = AOBUS_READ_4(AML_M8B_CPU_PWR_MEM_PD0_REG);
			 value &= ~((uint32_t)AML_M8B_CPU_PWR_MEM_PD0_CPU1 >>
			    ((cpu - 1) * 4));
			 AOBUS_WRITE_4(AML_M8B_CPU_PWR_MEM_PD0_REG, value);
			 AOBUS_BARRIER(AML_M8B_CPU_PWR_MEM_PD0_REG);
		 }

		/*
		 * Power on CPU.
		 */
		value = AOBUS_READ_4(AML_M8_CPU_PWR_CNTL1_REG);
		value &= ~(AML_M8_CPU_PWR_CNTL1_MODE_CPU1_MASK <<
		    ((cpu - 1) * 2));
		AOBUS_WRITE_4(AML_M8_CPU_PWR_CNTL1_REG, value);
		AOBUS_BARRIER(AML_M8_CPU_PWR_CNTL1_REG);

		DELAY(10);

		if (aml8726_soc_hw_rev == AML_SOC_HW_REV_M8B) {
			/*
			 * Wait for power on confirmation.
			 */
			for ( ; ; ) {
				value = AOBUS_READ_4(AML_M8_CPU_PWR_CNTL1_REG);
				value &= AML_M8B_CPU_PWR_CNTL1_PWR_CPU1 <<
				    (cpu - 1);
				if (value)
					break;
				DELAY(10);
			}
		}

		/*
		 * Release peripheral clamp.
		 */
		value = AOBUS_READ_4(AML_M8_CPU_PWR_CNTL0_REG);
		value &= ~(AML_M8_CPU_PWR_CNTL0_ISO_CPU1 << (cpu - 1));
		AOBUS_WRITE_4(AML_M8_CPU_PWR_CNTL0_REG, value);
		AOBUS_BARRIER(AML_M8_CPU_PWR_CNTL0_REG);

		/*
		 * Release reset.
		 */
		value = CBUS_READ_4(AML_SOC_CPU_CLK_CNTL_REG);
		value &= ~(AML_M8_CPU_CLK_CNTL_RESET_CPU1 << (cpu - 1));
		CBUS_WRITE_4(AML_SOC_CPU_CLK_CNTL_REG, value);
		CBUS_BARRIER(AML_SOC_CPU_CLK_CNTL_REG);

		if (aml8726_soc_hw_rev == AML_SOC_HW_REV_M8B) {
			/*
			 * The Amlogic Linux platform code sets the SCU power
			 * status for the CPU again for some reason so we
			 * follow suit (perhaps in case the reset caused
			 * a stale power status from the actual CPU to be
			 * written to the SCU).
			 */
			SCU_WRITE_4(AML_SCU_CPU_PWR_STATUS_REG, scpsr);
			SCU_BARRIER(AML_SCU_CPU_PWR_STATUS_REG);
		}
		break;
	default:
		break;
	}
}