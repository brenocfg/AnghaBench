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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_ini_bb_rfgain; } ;

/* Variables and functions */
 TYPE_1__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_ini_write (struct ath_hal*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar9287WriteRegs(struct ath_hal *ah, u_int modesIndex, u_int freqIndex,
	int writes)
{
	(void) ath_hal_ini_write(ah, &AH5416(ah)->ah_ini_bb_rfgain,
		freqIndex, writes);
}