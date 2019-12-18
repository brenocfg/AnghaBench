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

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MVPCONTROL_VPC ; 
 int /*<<< orphan*/  TCSTATUS_A ; 
 int /*<<< orphan*/  VPECONF0_VPA ; 
 scalar_t__ atomic_cmpset_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evpe () ; 
 int /*<<< orphan*/  malta_ap_boot ; 
 int /*<<< orphan*/  mftc0 (int,int) ; 
 int /*<<< orphan*/  mttc0 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  read_c0_register32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_thread_context (int) ; 
 int /*<<< orphan*/  write_c0_register32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
platform_start_ap(int cpuid)
{
	uint32_t reg;
	int timeout;

	/* Enter into configuration */
	reg = read_c0_register32(0, 1);
	reg |= (MVPCONTROL_VPC);
	write_c0_register32(0, 1, reg);

	set_thread_context(cpuid);

	/*
	 * Hint: how to set entry point.
	 * reg = 0x80000000;
	 * mttc0(2, 3, reg);
	 */

	/* Enable thread */
	reg = mftc0(2, 1);
	reg |= (TCSTATUS_A);
	mttc0(2, 1, reg);

	/* Unhalt CPU core */
	mttc0(2, 4, 0);

	/* Activate VPE */
	reg = mftc0(1, 2);
	reg |= (VPECONF0_VPA);
	mttc0(1, 2, reg);

	/* Out of configuration */
	reg = read_c0_register32(0, 1);
	reg &= ~(MVPCONTROL_VPC);
	write_c0_register32(0, 1, reg);

	evpe();

	if (atomic_cmpset_32(&malta_ap_boot, ~0, cpuid) == 0)
		return (-1);

	printf("Waiting for cpu%d to start\n", cpuid);

	timeout = 100;
	do {
		DELAY(1000);
		if (atomic_cmpset_32(&malta_ap_boot, 0, ~0) != 0) {
			printf("CPU %d started\n", cpuid);
			return (0);
		}
	} while (timeout--);

	printf("CPU %d failed to start\n", cpuid);

	return (0);
}