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
 int /*<<< orphan*/  FPU_illegal () ; 
 int FPU_rm ; 
 int /*<<< orphan*/  compare_st_st (int) ; 
 int /*<<< orphan*/  poppop () ; 

void fcompp(void)
{
	/* fcompp */
	if (FPU_rm != 1) {
		FPU_illegal();
		return;
	}
	if (!compare_st_st(1))
		poppop();
}