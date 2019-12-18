#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_hal {int /*<<< orphan*/  (* ah_resetKeyCacheEntry ) (struct ath_hal*,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* ah_setKeyCacheEntry ) (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int ah_11nCompat; int /*<<< orphan*/  ah_chansurvey; int /*<<< orphan*/ * ah_fatalState; int /*<<< orphan*/  ah_devid; } ;
struct TYPE_5__ {int /*<<< orphan*/  ee_data; int /*<<< orphan*/  ee_off; } ;
struct TYPE_4__ {int /*<<< orphan*/  dk_xor; int /*<<< orphan*/  dk_mac; int /*<<< orphan*/  dk_keyval; int /*<<< orphan*/  dk_keyix; } ;
typedef  int /*<<< orphan*/  HAL_REVS ;
typedef  TYPE_1__ HAL_DIAG_KEYVAL ;
typedef  TYPE_2__ HAL_DIAG_EEVAL ;
typedef  int /*<<< orphan*/  HAL_CHANNEL_SURVEY ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
#define  HAL_DIAG_11NCOMPAT 137 
#define  HAL_DIAG_CHANSURVEY 136 
#define  HAL_DIAG_EEREAD 135 
#define  HAL_DIAG_EEWRITE 134 
#define  HAL_DIAG_FATALERR 133 
#define  HAL_DIAG_REGS 132 
#define  HAL_DIAG_RESETKEY 131 
#define  HAL_DIAG_REVS 130 
#define  HAL_DIAG_SETKEY 129 
#define  HAL_DIAG_SETREGS 128 
 int /*<<< orphan*/  ath_hal_eepromRead (struct ath_hal*,int /*<<< orphan*/  const,void*) ; 
 int /*<<< orphan*/  ath_hal_eepromWrite (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath_hal_getregdump (struct ath_hal*,void const*,void*,int) ; 
 int /*<<< orphan*/  ath_hal_setregs (struct ath_hal*,void const*,int) ; 
 int /*<<< orphan*/  stub1 (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ath_hal*,int /*<<< orphan*/  const) ; 

HAL_BOOL
ath_hal_getdiagstate(struct ath_hal *ah, int request,
	const void *args, uint32_t argsize,
	void **result, uint32_t *resultsize)
{

	switch (request) {
	case HAL_DIAG_REVS:
		*result = &AH_PRIVATE(ah)->ah_devid;
		*resultsize = sizeof(HAL_REVS);
		return AH_TRUE;
	case HAL_DIAG_REGS:
		*resultsize = ath_hal_getregdump(ah, args, *result,*resultsize);
		return AH_TRUE;
	case HAL_DIAG_SETREGS:
		ath_hal_setregs(ah, args, argsize);
		*resultsize = 0;
		return AH_TRUE;
	case HAL_DIAG_FATALERR:
		*result = &AH_PRIVATE(ah)->ah_fatalState[0];
		*resultsize = sizeof(AH_PRIVATE(ah)->ah_fatalState);
		return AH_TRUE;
	case HAL_DIAG_EEREAD:
		if (argsize != sizeof(uint16_t))
			return AH_FALSE;
		if (!ath_hal_eepromRead(ah, *(const uint16_t *)args, *result))
			return AH_FALSE;
		*resultsize = sizeof(uint16_t);
		return AH_TRUE;
#ifdef AH_PRIVATE_DIAG
	case HAL_DIAG_SETKEY: {
		const HAL_DIAG_KEYVAL *dk;

		if (argsize != sizeof(HAL_DIAG_KEYVAL))
			return AH_FALSE;
		dk = (const HAL_DIAG_KEYVAL *)args;
		return ah->ah_setKeyCacheEntry(ah, dk->dk_keyix,
			&dk->dk_keyval, dk->dk_mac, dk->dk_xor);
	}
	case HAL_DIAG_RESETKEY:
		if (argsize != sizeof(uint16_t))
			return AH_FALSE;
		return ah->ah_resetKeyCacheEntry(ah, *(const uint16_t *)args);
#ifdef AH_SUPPORT_WRITE_EEPROM
	case HAL_DIAG_EEWRITE: {
		const HAL_DIAG_EEVAL *ee;
		if (argsize != sizeof(HAL_DIAG_EEVAL))
			return AH_FALSE;
		ee = (const HAL_DIAG_EEVAL *)args;
		return ath_hal_eepromWrite(ah, ee->ee_off, ee->ee_data);
	}
#endif /* AH_SUPPORT_WRITE_EEPROM */
#endif /* AH_PRIVATE_DIAG */
	case HAL_DIAG_11NCOMPAT:
		if (argsize == 0) {
			*resultsize = sizeof(uint32_t);
			*((uint32_t *)(*result)) =
				AH_PRIVATE(ah)->ah_11nCompat;
		} else if (argsize == sizeof(uint32_t)) {
			AH_PRIVATE(ah)->ah_11nCompat = *(const uint32_t *)args;
		} else
			return AH_FALSE;
		return AH_TRUE;
	case HAL_DIAG_CHANSURVEY:
		*result = &AH_PRIVATE(ah)->ah_chansurvey;
		*resultsize = sizeof(HAL_CHANNEL_SURVEY);
		return AH_TRUE;
	}
	return AH_FALSE;
}