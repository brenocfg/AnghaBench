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
typedef  int uint64_t ;
typedef  int register_t ;

/* Variables and functions */
 int PSL_EE ; 
 int SCOMC_WRITE ; 
 int /*<<< orphan*/  SPR_SCOMC ; 
 int /*<<< orphan*/  SPR_SCOMD ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtspr64 (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
write_scom(register_t address, uint64_t value)
{
	register_t msr;
	#ifndef __powerpc64__
	register_t hi, lo, scratch;
	#endif

	msr = mfmsr();
	mtmsr(msr & ~PSL_EE); isync();

	#ifdef __powerpc64__
	mtspr(SPR_SCOMD, value);
	#else
	hi = (value >> 32) & 0xffffffff;
	lo = value & 0xffffffff;
	mtspr64(SPR_SCOMD, hi, lo, scratch); 
	#endif
	isync();
	mtspr(SPR_SCOMC, address | SCOMC_WRITE);
	isync();

	mtmsr(msr); isync();
}