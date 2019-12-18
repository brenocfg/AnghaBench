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
typedef  int register_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int L3CR_L3CLKEN ; 
 int L3CR_L3E ; 
 int L3CR_L3I ; 
 int L3CR_L3PE ; 
 int /*<<< orphan*/  SPR_L3CR ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static register_t
mpc745x_l3_enable(register_t l3cr_config)
{
	register_t ccr;

	ccr = mfspr(SPR_L3CR);
	if (ccr & L3CR_L3E)
		return (ccr);

	/* Configure L3 cache. */
	ccr = l3cr_config & ~(L3CR_L3E | L3CR_L3I | L3CR_L3PE | L3CR_L3CLKEN);
	mtspr(SPR_L3CR, ccr);
	ccr |= 0x4000000;       /* Magic, but documented. */
	mtspr(SPR_L3CR, ccr);
	ccr |= L3CR_L3CLKEN;
	mtspr(SPR_L3CR, ccr);
	mtspr(SPR_L3CR, ccr | L3CR_L3I);
	while (mfspr(SPR_L3CR) & L3CR_L3I)
		;
	mtspr(SPR_L3CR, ccr & ~L3CR_L3CLKEN);
	powerpc_sync();
	DELAY(100);
	mtspr(SPR_L3CR, ccr);
	powerpc_sync();
	DELAY(100);
	ccr |= L3CR_L3E;
	mtspr(SPR_L3CR, ccr);
	powerpc_sync();

	return(ccr);
}