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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 

HAL_BOOL
ar5211SetupXTxDesc(struct ath_hal *ah, struct ath_desc *ds,
	u_int txRate1, u_int txTries1,
	u_int txRate2, u_int txTries2,
	u_int txRate3, u_int txTries3)
{
	(void) ah; (void) ds;
	(void) txRate1; (void) txTries1;
	(void) txRate2; (void) txTries2;
	(void) txRate3; (void) txTries3;
	return AH_FALSE;
}