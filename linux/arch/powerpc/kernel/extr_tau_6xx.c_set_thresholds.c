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
struct TYPE_2__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_THRM1 ; 
 int /*<<< orphan*/  SPRN_THRM2 ; 
 int THRM1_THRES (int /*<<< orphan*/ ) ; 
 int THRM1_TID ; 
 int THRM1_TIE ; 
 int THRM1_V ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tau ; 

__attribute__((used)) static void set_thresholds(unsigned long cpu)
{
#ifdef CONFIG_TAU_INT
	/*
	 * setup THRM1,
	 * threshold, valid bit, enable interrupts, interrupt when below threshold
	 */
	mtspr(SPRN_THRM1, THRM1_THRES(tau[cpu].low) | THRM1_V | THRM1_TIE | THRM1_TID);

	/* setup THRM2,
	 * threshold, valid bit, enable interrupts, interrupt when above threshold
	 */
	mtspr (SPRN_THRM2, THRM1_THRES(tau[cpu].high) | THRM1_V | THRM1_TIE);
#else
	/* same thing but don't enable interrupts */
	mtspr(SPRN_THRM1, THRM1_THRES(tau[cpu].low) | THRM1_V | THRM1_TID);
	mtspr(SPRN_THRM2, THRM1_THRES(tau[cpu].high) | THRM1_V);
#endif
}