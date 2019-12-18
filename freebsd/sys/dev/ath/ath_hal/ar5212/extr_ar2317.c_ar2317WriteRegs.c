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
typedef  int u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_INI_WRITE_ARRAY (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ar5212BB_RfGain_2317 ; 
 int /*<<< orphan*/  ar5212Common_2317 ; 
 int /*<<< orphan*/  ar5212Modes_2317 ; 

__attribute__((used)) static void
ar2317WriteRegs(struct ath_hal *ah, u_int modesIndex, u_int freqIndex,
	int writes)
{
	HAL_INI_WRITE_ARRAY(ah, ar5212Modes_2317, modesIndex, writes);
	HAL_INI_WRITE_ARRAY(ah, ar5212Common_2317, 1, writes);
	HAL_INI_WRITE_ARRAY(ah, ar5212BB_RfGain_2317, freqIndex, writes);
}