#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int cols; int rows; } ;
typedef  TYPE_1__ HAL_INI_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_YIELD (int) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int HAL_INI_VAL (TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 

int
ath_hal_ini_write(struct ath_hal *ah, const HAL_INI_ARRAY *ia,
	int col, int regWr)
{
	int r;

	HALASSERT(col < ia->cols);
	for (r = 0; r < ia->rows; r++) {
		OS_REG_WRITE(ah, HAL_INI_VAL(ia, r, 0),
		    HAL_INI_VAL(ia, r, col));

		/* Analog shift register delay seems needed for Merlin - PR kern/154220 */
		if (HAL_INI_VAL(ia, r, 0) >= 0x7800 && HAL_INI_VAL(ia, r, 0) < 0x7900)
			OS_DELAY(100);

		DMA_YIELD(regWr);
	}
	return regWr;
}