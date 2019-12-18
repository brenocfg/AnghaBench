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
typedef  int uint16_t ;
typedef  int register_t ;

/* Variables and functions */
 int L2CR_L2E ; 
 int L2CR_L2I ; 
 int L2CR_L2IP ; 
#define  MPC7400 129 
#define  MPC7410 128 
 int /*<<< orphan*/  SPR_L2CR ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static register_t
mpc74xx_l2_enable(register_t l2cr_config)
{
	register_t ccr, bit;
	uint16_t	vers;

	vers = mfpvr() >> 16;
	switch (vers) {
	case MPC7400:
	case MPC7410:
		bit = L2CR_L2IP;
		break;
	default:
		bit = L2CR_L2I;
		break;
	}

	ccr = mfspr(SPR_L2CR);
	if (ccr & L2CR_L2E)
		return (ccr);

	/* Configure L2 cache. */
	ccr = l2cr_config & ~L2CR_L2E;
	mtspr(SPR_L2CR, ccr | L2CR_L2I);
	do {
		ccr = mfspr(SPR_L2CR);
	} while (ccr & bit);
	powerpc_sync();
	mtspr(SPR_L2CR, l2cr_config);
	powerpc_sync();

	return (l2cr_config);
}