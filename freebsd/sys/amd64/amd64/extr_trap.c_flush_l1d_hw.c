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
 int /*<<< orphan*/  IA32_FLUSH_CMD_L1D ; 
 int /*<<< orphan*/  MSR_IA32_FLUSH_CMD ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_l1d_hw(void)
{

	wrmsr(MSR_IA32_FLUSH_CMD, IA32_FLUSH_CMD_L1D);
}