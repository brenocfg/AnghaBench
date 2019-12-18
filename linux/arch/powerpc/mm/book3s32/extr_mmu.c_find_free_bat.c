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
struct ppc_bat {int batl; int batu; } ;

/* Variables and functions */
 struct ppc_bat** BATS ; 
 int /*<<< orphan*/  CONFIG_PPC_BOOK3S_601 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_FTR_USE_HIGH_BATS ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_free_bat(void)
{
	int b;

	if (IS_ENABLED(CONFIG_PPC_BOOK3S_601)) {
		for (b = 0; b < 4; b++) {
			struct ppc_bat *bat = BATS[b];

			if (!(bat[0].batl & 0x40))
				return b;
		}
	} else {
		int n = mmu_has_feature(MMU_FTR_USE_HIGH_BATS) ? 8 : 4;

		for (b = 0; b < n; b++) {
			struct ppc_bat *bat = BATS[b];

			if (!(bat[1].batu & 3))
				return b;
		}
	}
	return -1;
}