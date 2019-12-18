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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AR_PCICFG ; 
 int AR_PCICFG_EEPROMSEL ; 
#define  HAL_DIAG_EEPROM 129 
#define  HAL_DIAG_EEREAD 128 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_eepromRead (struct ath_hal*,int /*<<< orphan*/  const,void*) ; 
 int /*<<< orphan*/  ath_hal_getdiagstate (struct ath_hal*,int,void const*,int,void**,int*) ; 

HAL_BOOL
ar5210GetDiagState(struct ath_hal *ah, int request,
	const void *args, uint32_t argsize,
	void **result, uint32_t *resultsize)
{
#ifdef AH_PRIVATE_DIAG
	uint32_t pcicfg;
	HAL_BOOL ok;

	switch (request) {
	case HAL_DIAG_EEPROM:
		/* XXX */
		break;
	case HAL_DIAG_EEREAD:
		if (argsize != sizeof(uint16_t))
			return AH_FALSE;
		pcicfg = OS_REG_READ(ah, AR_PCICFG);
		OS_REG_WRITE(ah, AR_PCICFG, pcicfg | AR_PCICFG_EEPROMSEL);
		ok = ath_hal_eepromRead(ah, *(const uint16_t *)args, *result);
		OS_REG_WRITE(ah, AR_PCICFG, pcicfg);
		if (ok)
			*resultsize = sizeof(uint16_t);
		return ok;
	}
#endif
	return ath_hal_getdiagstate(ah, request,
		args, argsize, result, resultsize);
}