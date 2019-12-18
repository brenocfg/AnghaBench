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
typedef  int /*<<< orphan*/  const HAL_RATE_TABLE ;

/* Variables and functions */
#define  HAL_MODE_11NA_HT20 133 
#define  HAL_MODE_11NA_HT40MINUS 132 
#define  HAL_MODE_11NA_HT40PLUS 131 
#define  HAL_MODE_11NG_HT20 130 
#define  HAL_MODE_11NG_HT40MINUS 129 
#define  HAL_MODE_11NG_HT40PLUS 128 
 int /*<<< orphan*/  const* ar5212GetRateTable (struct ath_hal*,int) ; 
 int /*<<< orphan*/  const ar5416_11na_table ; 
 int /*<<< orphan*/  const ar5416_11ng_table ; 
 int /*<<< orphan*/  ath_hal_setupratetable (struct ath_hal*,int /*<<< orphan*/  const*) ; 

const HAL_RATE_TABLE *
ar5416GetRateTable(struct ath_hal *ah, u_int mode)
{
	HAL_RATE_TABLE *rt;
	switch (mode) {
	case HAL_MODE_11NG_HT20:
	case HAL_MODE_11NG_HT40PLUS:
	case HAL_MODE_11NG_HT40MINUS:
		rt = &ar5416_11ng_table;
		break;
	case HAL_MODE_11NA_HT20:
	case HAL_MODE_11NA_HT40PLUS:
	case HAL_MODE_11NA_HT40MINUS:
		rt = &ar5416_11na_table;
		break;
	default:
		return ar5212GetRateTable(ah, mode);
	}
	ath_hal_setupratetable(ah, rt);
	return rt;
}