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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_OPMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PCICFG ; 
 int /*<<< orphan*/  AR_PCICFG_SCLK_RATE_IND ; 
 int /*<<< orphan*/  AR_PCICFG_SCLK_SEL ; 
 int /*<<< orphan*/  AR_PHY_M_SLEEP ; 
 int /*<<< orphan*/  AR_PHY_REFCLKDLY ; 
 int /*<<< orphan*/  AR_PHY_REFCLKPD ; 
 int /*<<< orphan*/  AR_PHY_SLEEP_CTR_CONTROL ; 
 int /*<<< orphan*/  AR_PHY_SLEEP_CTR_LIMIT ; 
 int /*<<< orphan*/  AR_PHY_SLEEP_SCAL ; 
 int /*<<< orphan*/  AR_TSF_PARM ; 
 int /*<<< orphan*/  AR_USEC ; 
 int /*<<< orphan*/  AR_USEC_USEC32 ; 
 scalar_t__ IS_2413 (struct ath_hal*) ; 
 scalar_t__ IS_2417 (struct ath_hal*) ; 
 scalar_t__ IS_5413 (struct ath_hal*) ; 
 scalar_t__ IS_HB63 (struct ath_hal*) ; 
 scalar_t__ IS_RAD5112_ANY (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ar5212Use32KHzclock (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ar5212SetupClock(struct ath_hal *ah, HAL_OPMODE opmode)
{
	if (ar5212Use32KHzclock(ah, opmode)) {
		/*
		 * Enable clocks to be turned OFF in BB during sleep
		 * and also enable turning OFF 32MHz/40MHz Refclk
		 * from A2.
		 */
		OS_REG_WRITE(ah, AR_PHY_SLEEP_CTR_CONTROL, 0x1f);
		OS_REG_WRITE(ah, AR_PHY_REFCLKPD,
		    IS_RAD5112_ANY(ah) || IS_5413(ah) ? 0x14 : 0x18);
		OS_REG_RMW_FIELD(ah, AR_USEC, AR_USEC_USEC32, 1);
		OS_REG_WRITE(ah, AR_TSF_PARM, 61);  /* 32 KHz TSF incr */
		OS_REG_RMW_FIELD(ah, AR_PCICFG, AR_PCICFG_SCLK_SEL, 1);

		if (IS_2413(ah) || IS_5413(ah) || IS_2417(ah)) {
			OS_REG_WRITE(ah, AR_PHY_SLEEP_CTR_LIMIT,   0x26);
			OS_REG_WRITE(ah, AR_PHY_SLEEP_SCAL,        0x0d);
			OS_REG_WRITE(ah, AR_PHY_M_SLEEP,           0x07);
			OS_REG_WRITE(ah, AR_PHY_REFCLKDLY,         0x3f);
			/* # Set sleep clock rate to 32 KHz. */
			OS_REG_RMW_FIELD(ah, AR_PCICFG, AR_PCICFG_SCLK_RATE_IND, 0x2);
		} else {
			OS_REG_WRITE(ah, AR_PHY_SLEEP_CTR_LIMIT,   0x0a);
			OS_REG_WRITE(ah, AR_PHY_SLEEP_SCAL,        0x0c);
			OS_REG_WRITE(ah, AR_PHY_M_SLEEP,           0x03);
			OS_REG_WRITE(ah, AR_PHY_REFCLKDLY,         0x20);
			OS_REG_RMW_FIELD(ah, AR_PCICFG, AR_PCICFG_SCLK_RATE_IND, 0x3);
		}
	} else {
		OS_REG_RMW_FIELD(ah, AR_PCICFG, AR_PCICFG_SCLK_RATE_IND, 0x0);
		OS_REG_RMW_FIELD(ah, AR_PCICFG, AR_PCICFG_SCLK_SEL, 0);

		OS_REG_WRITE(ah, AR_TSF_PARM, 1);	/* 32MHz TSF inc */

		OS_REG_WRITE(ah, AR_PHY_SLEEP_CTR_CONTROL, 0x1f);
		OS_REG_WRITE(ah, AR_PHY_SLEEP_CTR_LIMIT,   0x7f);

		if (IS_2417(ah))
			OS_REG_WRITE(ah, AR_PHY_SLEEP_SCAL, 0x0a);
		else if (IS_HB63(ah))
			OS_REG_WRITE(ah, AR_PHY_SLEEP_SCAL, 0x32);
		else
			OS_REG_WRITE(ah, AR_PHY_SLEEP_SCAL, 0x0e);
		OS_REG_WRITE(ah, AR_PHY_M_SLEEP,           0x0c);
		OS_REG_WRITE(ah, AR_PHY_REFCLKDLY,         0xff);
		OS_REG_WRITE(ah, AR_PHY_REFCLKPD,
		    IS_RAD5112_ANY(ah) || IS_5413(ah) || IS_2417(ah) ? 0x14 : 0x18);
		OS_REG_RMW_FIELD(ah, AR_USEC, AR_USEC_USEC32,
		    IS_RAD5112_ANY(ah) || IS_5413(ah) ? 39 : 31);
	}
}