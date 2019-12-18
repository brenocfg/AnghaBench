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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_maskReg; } ;

/* Variables and functions */
 TYPE_1__* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_GPIOCR ; 
 int AR_GPIOCR_CR_A (int /*<<< orphan*/ ) ; 
 int AR_GPIOCR_CR_N (int /*<<< orphan*/ ) ; 
 int AR_GPIOCR_INT (int /*<<< orphan*/ ) ; 
 int AR_GPIOCR_INT_ENA ; 
 int AR_GPIOCR_INT_MASK ; 
 int AR_GPIOCR_INT_SEL ; 
 int AR_GPIOCR_INT_SELH ; 
 int AR_GPIOCR_INT_SELL ; 
 int HAL_INT_GPIO ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212SetInterrupts (struct ath_hal*,int) ; 

void
ar5212GpioSetIntr(struct ath_hal *ah, u_int gpio, uint32_t ilevel)
{
	uint32_t val;

	/* XXX bounds check gpio */
	val = OS_REG_READ(ah, AR_GPIOCR);
	val &= ~(AR_GPIOCR_CR_A(gpio) |
		 AR_GPIOCR_INT_MASK | AR_GPIOCR_INT_ENA | AR_GPIOCR_INT_SEL);
	val |= AR_GPIOCR_CR_N(gpio) | AR_GPIOCR_INT(gpio) | AR_GPIOCR_INT_ENA;
	if (ilevel)
		val |= AR_GPIOCR_INT_SELH;	/* interrupt on pin high */
	else
		val |= AR_GPIOCR_INT_SELL;	/* interrupt on pin low */

	/* Don't need to change anything for low level interrupt. */
	OS_REG_WRITE(ah, AR_GPIOCR, val);

	/* Change the interrupt mask. */
	(void) ar5212SetInterrupts(ah, AH5212(ah)->ah_maskReg | HAL_INT_GPIO);
}